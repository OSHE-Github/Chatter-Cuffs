#pragma once

class Output;
class I2SSampler;
class Transport;
class OutputBuffer;
class IndicatorLed;

class Application
{
private:
  Output *m_output;
  I2SSampler *m_input;
  Transport *m_transport;
  IndicatorLed *m_indicator_led;
  OutputBuffer *m_output_buffer;
  
  // Volume control variables
  uint8_t m_volume_level;  // 0-100 (percentage)
  unsigned long m_last_volume_button_time;
  static const uint8_t VOLUME_MIN = 0;
  static const uint8_t VOLUME_MAX = 100;
  static const unsigned long VOLUME_BUTTON_DEBOUNCE_MS = 200;
  
  // Channel control variables
  uint8_t m_current_channel;  // Current ESP-NOW channel (1-11)
  unsigned long m_last_channel_button_time;
  static const unsigned long CHANNEL_BUTTON_DEBOUNCE_MS = 200;

public:
  Application();
  void begin();
  void loop();

private:
  void handle_volume_buttons();
  void handle_channel_buttons();
  void apply_volume_to_samples(int16_t *samples, int count);
  void change_channel(uint8_t new_channel);
};
