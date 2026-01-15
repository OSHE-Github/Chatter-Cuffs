#include <Arduino.h>
#include <driver/i2s.h>
#include <WiFi.h>

#include "Application.h"
#include "I2SMEMSSampler.h"
#include "ADCSampler.h"
#include "I2SOutput.h"
#include "DACOutput.h"
#include "UdpTransport.h"
#include "EspNowTransport.h"
#include "OutputBuffer.h"
#include "config.h"

#ifdef ARDUINO_TINYPICO
#include "TinyPICOIndicatorLed.h"
#else
#include "GenericDevBoardIndicatorLed.h"
#endif

static void application_task(void *param)
{
  // delegate onto the application
  Application *application = reinterpret_cast<Application *>(param);
  application->loop();
}

Application::Application()
{
  m_output_buffer = new OutputBuffer(300 * 16);
  
  // Initialize volume control
  m_volume_level = 50;  // Start at 50% volume
  m_last_volume_button_time = 0;
  
  // Initialize channel control
  m_current_channel = ESP_NOW_WIFI_CHANNEL;  // Start with default channel
  m_last_channel_button_time = 0;
#ifdef USE_I2S_MIC_INPUT
  m_input = new I2SMEMSSampler(I2S_NUM_0, i2s_mic_pins, i2s_mic_Config,128);
#else
  m_input = new ADCSampler(ADC_UNIT_1, ADC1_CHANNEL_7, i2s_adc_config);
#endif

#ifdef USE_I2S_SPEAKER_OUTPUT
  m_output = new I2SOutput(I2S_NUM_0, i2s_speaker_pins);
#else
  m_output = new DACOutput(I2S_NUM_0);
#endif

#ifdef USE_ESP_NOW
  m_transport = new EspNowTransport(m_output_buffer,ESP_NOW_WIFI_CHANNEL);
#else
  m_transport = new UdpTransport(m_output_buffer);
#endif

  m_transport->set_header(TRANSPORT_HEADER_SIZE,transport_header);

#ifdef ARDUINO_TINYPICO
  m_indicator_led = new TinyPICOIndicatorLed();
#else
  m_indicator_led = new GenericDevBoardIndicatorLed();
#endif

  if (I2S_SPEAKER_SD_PIN != -1)
  {
    pinMode(I2S_SPEAKER_SD_PIN, OUTPUT);
  }
}

void Application::begin()
{
  // show a flashing indicator that we are trying to connect
  m_indicator_led->set_default_color(0);
  m_indicator_led->set_is_flashing(true, 0xff0000);
  m_indicator_led->begin();

  Serial.print("My IDF Version is: ");
  Serial.println(esp_get_idf_version());

  // bring up WiFi
  WiFi.mode(WIFI_STA);
#ifndef USE_ESP_NOW
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  // this has a dramatic effect on packet RTT
  WiFi.setSleep(WIFI_PS_NONE);
  Serial.print("My IP Address is: ");
  Serial.println(WiFi.localIP());
#else
  // but don't connect if we're using ESP NOW
  WiFi.disconnect();
#endif
  Serial.print("My MAC Address is: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Starting on ESP-NOW Channel: ");
  Serial.println(m_current_channel);
  // do any setup of the transport
  m_transport->begin();
  // connected so show a solid green light
  m_indicator_led->set_default_color(0x00ff00);
  m_indicator_led->set_is_flashing(false, 0x00ff00);
  // setup the transmit button
  pinMode(GPIO_TRANSMIT_BUTTON, INPUT_PULLDOWN);
  // setup the volume control buttons
  pinMode(GPIO_VOLUME_UP_BUTTON, INPUT_PULLDOWN);
  pinMode(GPIO_VOLUME_DOWN_BUTTON, INPUT_PULLDOWN);
  // setup the channel control buttons
  pinMode(GPIO_CHANNEL_UP_BUTTON, INPUT_PULLDOWN);
  pinMode(GPIO_CHANNEL_DOWN_BUTTON, INPUT_PULLDOWN);
  // start off with i2S output running
  m_output->start(SAMPLE_RATE);
  // flush all samples received during startup
  m_output_buffer->flush();
  // start the main task for the application
  TaskHandle_t task_handle;
  xTaskCreate(application_task, "application_task", 8192, this, 1, &task_handle);
}

// application task - coordinates everything
void Application::loop()
{
  int16_t *samples = reinterpret_cast<int16_t *>(malloc(sizeof(int16_t) * 128));
  // continue forever
  while (true)
  {
    // do we need to start transmitting?
    if (digitalRead(GPIO_TRANSMIT_BUTTON))
    {
      Serial.println("Started transmitting");
      m_indicator_led->set_is_flashing(true, 0xff0000);
      // stop the output as we're switching into transmit mode
      m_output->stop();
      // start the input to get samples from the microphone
      m_input->start();
      // transmit for at least 1 second or while the button is pushed
      unsigned long start_time = millis();
      while (millis() - start_time < 1000 || digitalRead(GPIO_TRANSMIT_BUTTON))
      {
        // read samples from the microphone
        int samples_read = m_input->read(samples, 128);
        // and send them over the transport
        for (int i = 0; i < samples_read; i++)
        {
          m_transport->add_sample(samples[i]);
        }
      }
      // send all packets still in the transport buffer
      m_transport->flush();
      // finished transmitting stop the input and start the output
      Serial.println("Finished transmitting");
      m_indicator_led->set_is_flashing(false, 0xff0000);
      m_input->stop();
      m_output->start(SAMPLE_RATE);
    }
    // while the transmit button is not pushed and 1 second has not elapsed
    Serial.println("Started Receiving");
    if (I2S_SPEAKER_SD_PIN != -1)
    {
      digitalWrite(I2S_SPEAKER_SD_PIN, HIGH);
    }
    unsigned long start_time = millis();
    while (millis() - start_time < 1000 || !digitalRead(GPIO_TRANSMIT_BUTTON))
    {
      // handle volume control buttons
      handle_volume_buttons();
      
      // handle channel control buttons
      handle_channel_buttons();
      
      // read from the output buffer (which should be getting filled by the transport)
      m_output_buffer->remove_samples(samples, 128);
      // apply volume control to samples
      apply_volume_to_samples(samples, 128);
      // and send the samples to the speaker
      m_output->write(samples, 128);
    }
    if (I2S_SPEAKER_SD_PIN != -1)
    {
      digitalWrite(I2S_SPEAKER_SD_PIN, LOW);
    }
    Serial.println("Finished Receiving");
  }
}

void Application::handle_volume_buttons()
{
  unsigned long current_time = millis();
  
  // Debounce check
  if (current_time - m_last_volume_button_time < VOLUME_BUTTON_DEBOUNCE_MS)
  {
    return;
  }
  
  // Check volume up button
  if (digitalRead(GPIO_VOLUME_UP_BUTTON))
  {
    if (m_volume_level < VOLUME_MAX)
    {
      m_volume_level += 5;  // Increase volume by 5%
      if (m_volume_level > VOLUME_MAX) m_volume_level = VOLUME_MAX;
      Serial.print("Volume up: ");
      Serial.println(m_volume_level);
      m_last_volume_button_time = current_time;
    }
  }
  
  // Check volume down button
  if (digitalRead(GPIO_VOLUME_DOWN_BUTTON))
  {
    if (m_volume_level > VOLUME_MIN)
    {
      m_volume_level -= 5;  // Decrease volume by 5%
      if (m_volume_level < VOLUME_MIN) m_volume_level = VOLUME_MIN;
      Serial.print("Volume down: ");
      Serial.println(m_volume_level);
      m_last_volume_button_time = current_time;
    }
  }
}

void Application::apply_volume_to_samples(int16_t *samples, int count)
{
  if (m_volume_level == 100)
  {
    // No scaling needed at 100% volume
    return;
  }
  
  // Scale samples by volume level (0-100%)
  for (int i = 0; i < count; i++)
  {
    // Convert to 32-bit for calculation to avoid overflow
    int32_t scaled_sample = (int32_t)samples[i] * m_volume_level / 100;
    
    // Clamp to 16-bit range
    if (scaled_sample > 32767) scaled_sample = 32767;
    if (scaled_sample < -32768) scaled_sample = -32768;
    
    samples[i] = (int16_t)scaled_sample;
  }
}

void Application::handle_channel_buttons()
{
  unsigned long current_time = millis();
  
  // Debounce check
  if (current_time - m_last_channel_button_time < CHANNEL_BUTTON_DEBOUNCE_MS)
  {
    return;
  }
  
  // Check channel up button (D2 - GPIO2, active LOW with pullup)
  if (digitalRead(GPIO_CHANNEL_UP_BUTTON))
  {
    if (m_current_channel < ESP_NOW_CHANNEL_MAX)
    {
      change_channel(m_current_channel + 1);
      m_last_channel_button_time = current_time;
    }
  }
  
  // Check channel down button (D4 - GPIO4, active LOW with pullup)
  if (digitalRead(GPIO_CHANNEL_DOWN_BUTTON))
  {
    if (m_current_channel > ESP_NOW_CHANNEL_MIN)
    {
      change_channel(m_current_channel - 1);
      m_last_channel_button_time = current_time;
    }
  }
}

void Application::change_channel(uint8_t new_channel)
{
  if (new_channel < ESP_NOW_CHANNEL_MIN || new_channel > ESP_NOW_CHANNEL_MAX)
  {
    return; // Invalid channel
  }
  
  if (new_channel == m_current_channel)
  {
    return; // Already on this channel
  }
  
  Serial.print("Changing channel from ");
  Serial.print(m_current_channel);
  Serial.print(" to ");
  Serial.println(new_channel);
  
  // Flash LED to indicate channel change
  m_indicator_led->set_is_flashing(true, 0x0000ff); // Blue flash for channel change
  
  m_current_channel = new_channel;
  
#ifdef USE_ESP_NOW
  // Cast to EspNowTransport to access channel change method
  EspNowTransport* espnow_transport = static_cast<EspNowTransport*>(m_transport);
  if (espnow_transport)
  {
    espnow_transport->change_channel(new_channel);
  }
  
  // Stop LED flashing after channel change
  m_indicator_led->set_is_flashing(false, 0x0000ff); // Back to blue
#endif
}
