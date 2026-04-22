# Chatter Cuff
Chatter Cuff is a wrist mounted walkie talkie intended for outdoor sporting enthusiasts.
<br/>

<p align="center">
  <img width="200" alt="oshe logo" src="https://github.com/user-attachments/assets/61bf5a2a-98b7-4360-a7c4-535ba3543745" />
<p/>

## Project Details
The Chatter Cuff is a student-led project sponsored by the OSHE enterprise, created to solve the limitations of traditional walkie talkies in cold-weather sports. Designed as a forearm-mounted communication device, it offers glove-friendly usability, weather-resistant electronics, and comfortable wearability. This is made ideal for skiers, snowboarders, and outdoor adventurers who need reliable communication in remote environments. Over the course of two semesters, the team prototyped, refined, and finalized a durable, user-friendly product that reimagines how slope-side communication can be both practical and intuitive. By prioritizing comfort, durability, and ease of use, the Chatter Cuff represents a meaningful leap in wearable technology for outdoor recreation.


Beyond its immediate benefits to adventurers, the project provided students with a hands-on opportunity to integrate electronics, CAD design, and user-centered engineering into a real-world product. For the broader industry, it introduces a new user experience that could influence future designs in sports technology, emergency response gear, and wearable electronics. As for the OSHE enterprise, the Chatter Cuff offers visibility and recognition as the device is seen in action on the slopes. In combining technical innovation with practical usability, this project not only enhances safety and connectivity in extreme environments but also positions itself as a showcase of student ingenuity and enterprise impact.


The Chatter Cuff project provides a mostly unique take on the walkie talkie format, providing users with a glove enclosure to slip under jackets and gloves for ease of use and comfort. Using an ESP32-C3-WROOM and 
the ESP-NOW wireless communication protocol, 2 Chatter Cuffs can communicate back and forth with ease.

<p align="center">
  <img alt="An open chatter cuff" src="/Documents/chatter1.png" />
<p/>

<p align="center">
  <img alt="A closed chatter cuff" src="/Documents/chatter2.png" />
<p/>


## Repository Structure
Here is what's in each folder:
1. [Documents](https://github.com/OSHE-Github/Chatter-Cuffs/tree/main/Documents)
    - Documentation about the project including testing results
    - Media files for readmes
2. [Hardware](https://github.com/OSHE-Github/Chatter-Cuffs/tree/main/Hardware)
    - Gerber files and other resources for making your own Chatter Cuff
3. [walkie-talkie](https://github.com/OSHE-Github/Chatter-Cuffs/tree/main/walkie-talkie)
    - Project code and libraries


## Tools Used
| Tool/Programs                                              | Description                                                          |
| ---------------------------------------------------------- | -------------------------------------------------------------------- |
| Heat Gun (or reflow oven if available)                     | To solder the small SMT components                                   |
| Solder Paste                                               | Used in tandem with Heat Gun                                         |
| Soldering Iron                                             | Creating electrical connections between the wires                    |
| Screwdriver                                                | Screwed the enclosure together                                       |
| Tweesers                                                   | Component Placement                                                  |
| Flux                                                       | Tinning wires                                                        |
| Wire Strippers/Cutters                                     | Stripping Wires for transmit button                                  |
| Needle with Thread                                         | Seating the button on the compression glove for the device.          |
| Hobby Knife                                                | To spread solder paste on circuit board                              |
| 3D Printer (Used an X1 Carbon but could be any 3D printer) | Printed the enclosure for all the components                         |
| OnShape                                                    | Program used to model the enclosure to then export, slice, and print |
| Bambu Studio                                               | Slicer used to print the enclosure                                   |
| Platform IO in VS code                                     | For creating the program and programming the ESP-32                  |
| KiCAD                                                      | Designing the condensed PCB                                          |

### Features
- Long-range ESP-32 based transmission and receiving
- Battery power for extended outdoor use
- Tough external shell designed to be impact resistant
- Easily accessible transmit button and volume/channel switching buttons

### Bill of Materials
| Part Number        | Description                               | Designator                                                                        | Cost   | Quantity | Total Cost |
| ------------------ | ----------------------------------------- | --------------------------------------------------------------------------------- | ------ | -------- | ---------- |
| SM02B-SRSS-TB      | Battery Connector                         | Batt                                                                              | $0.38  | 1        | $0.38      |
| GMT21X7R105K25NT3  | 1uF Cap (Ceramic)                         | C1, C11, C13                                                                      | $0.20  | 3        | $0.60      |
| C0805C104K5RAC7210 | 0.1uF Cap (Ceramic)                       | C2, C4, C7, C8, C14                                                               | $0.13  | 5        | $0.65      |
| T491A475K025AT     | 4.7uF Cap (Tantalum)                      | C3                                                                                | $0.46  | 1        | $0.46      |
| C0805C104K5RAC7210 | 0.1uF Cap (Tantalum)                      | C5, C9, C17                                                                       | $0.13  | 3        | $0.39      |
| T491A106M010AT     | 10uF Cap (Tantalum)                       | C6, C10, C16                                                                      | $0.13  | 3        | $0.39      |
| C0805C106K8PACTU   | 10 uF Cap  (Ceramic)                      | C12                                                                               | $0.39  | 1        | $0.39      |
| CHV0805N250221FCT  | 220pF Cap  (Ceramic)                      | C15, C18                                                                          | $0.42  | 2        | $0.84      |
| 1825910-6          | TH Push Buttons                           | Ch+, Ch-, Vol+, Vol-                                                              | $0.13  | 4        | $0.52      |
| LTST-C170KRKT      | Red SMT LEDs                              | CH, Vol, L1, L2, L3, L4, RX, LED3, PWR                                            | $0.15  | 9        | $1.35      |
| 0ZCH0110AF2E       | Fuse (1.1A, 16V, 1210)                    | F1                                                                                | $0.31  | 1        | $0.31      |
| MI1206L501R-10     | Ferrite Beads                             | FB1, FB2                                                                          | $0.23  | 2        | $0.46      |
| MAX98357AETE+T     | Amplifier IC                              | U9                                                                                | $3.73  | 1        | $3.73      |
| 1003-030-01210-TR  | USB-C                                     | J1                                                                                | $0.98  | 1        | $0.98      |
| STX-3000           | Audio Jack                                | Jack                                                                              | $0.65  | 1        | $0.65      |
| LTST-C170TBKT      | Blue SMT LED                              | LED1                                                                              | $0.23  | 1        | $0.23      |
| LTST-C170GK        | Green SMT LED                             | LED2, TX                                                                          | $0.10  | 2        | $0.20      |
| MMICT5837-00-012   | New SMT Microphone                        | MIC                                                                               | $2.40  | 1        | $2.40      |
| JS102011SAQN       | SMT Switch                                | On/Off, SW                                                                        | $0.78  | 2        | $1.56      |
| BCW66HTA           | Transistors                               | Q1, Q2                                                                            | $0.39  | 2        | $0.78      |
| RC0805FR-1022K1L   | 22.1k Resistor                            | R1                                                                                | $0.10  | 1        | $0.10      |
| RC0805FR-0747K5L   | 47.5k Resistor                            | R2                                                                                | $0.10  | 1        | $0.10      |
| RC0805JR-075K1L    | 5.1k Resistor                             | R3, R11                                                                           | $0.10  | 2        | $0.20      |
| RC0805JR-131KL     | 1k Resistor                               | R4                                                                                | $0.10  | 1        | $0.10      |
| RC0805JR-070RL     | 0-Ohm Resistor                            | R5, R6                                                                            | $0.10  | 2        | $0.20      |
| RC0805FR-07470RL   | 470 Ohm Resistor                          | R7, R9, R10, R12, R13, R14, R15, R16, R17, R18, R19, R20, R21, R22, R23, R24, R26 | $0.10  | 17       | $1.70      |
| ESP32-C3-WROOM-02U | ESP-32                                    | U3                                                                                | $3.50  | 1        | $3.50      |
| RC0805FR-0747KL    | 4.7k Resistor                             | R8                                                                                | $0.10  | 1        | $0.10      |
| RC0805FR-07100KL   | 100k Resistor                             | R25                                                                               | $0.10  | 1        | $0.10      |
| RC0805JR-071ML     | 1M Resistor                               | R27                                                                               | $0.10  | 1        | $0.10      |
| RC0805FR-0710KL    | 10k Resistor                              | R28, R29, R30, R31, R32                                                           | $0.10  | 5        | $0.50      |
| RC0805FR-102KL     | 2k Resistor                               | R33                                                                               | $0.10  | 1        | $0.10      |
| RC0805FR-0720KL    | 20k Resistor                              | R34                                                                               | $0.10  | 1        | $0.10      |
| USLPT2819DT2TR     | SMT Buttons (boot/reset)                  | Boot, Reset                                                                       | $0.81  | 2        | $1.62      |
| CMS-151125-078L100 | Speaker (8 ohm)                           | Speaker                                                                           | $2.96  | 1        | $2.96      |
| CP2102N-A02-GQFN20 | USB Bridge, USB to UART                   | U2                                                                                | $4.48  | 1        | $4.48      |
| USBLC6-2SC6        | TVS Diode                                 | U1                                                                                | $0.36  | 1        | $0.36      |
| LM1117MPX-3.3/NOPB | Linear Regulator                          | VR1                                                                               | 1.07   | 1        | $1.07      |
| MCP73871T-1AAI/ML  | Battery Management IC                     | U5                                                                                | $2.41  | 1        | $2.41      |
| ASR00008           | 3.7V, 11mah Lith/ION Battery              | N/A                                                                               | $9.95  | 1        | $9.95      |
| N/A                | Compression Glove                         | N/A                                                                               | $15.99 | 1        | 15.99      |
| N/A                | ⅛ inch plastic elastic cord               | N/A                                                                               | $1.49  | 1        | 1.49       |
| N/A                | External Push Button                      | TXC                                                                               | $1.30  | 1        | $1.30      |
| N/A                | Bare PCBs (JLCPCB, 5 boards at about $60) | N/A                                                                               | $12    | 1        | $12        |
| N/A                | PCB Stencil                               | N/A                                                                               | $5     | 1        | $5         |
| N/A                | Needle and thread                         | N/A                                                                               | $3     | 1        | $3         |

## Assembly Instructions
Start by printing the provided files. PETG is recommended for the main enclosure, as its rigidity is preferred for ruggedness. PLA is recommended for the top to allow buttons to work. If applicable, TPU must be used for the optional gaskets. 


For the main circuit board, utilizing solder paste and a reflow oven is recommended, but not required. It is recommended to purchase solder paste and a stencil for the small surface mount components such as the QFN-20 and to use a heat gun to adhere those components to the PCB. Begin by aligning the stencil to the pads on the PCB. Dispense room temperature solder paste along the openings on the stencil then use a razor blade to evenly spread the paste along the stencil. It is recommended that you only place solder paste on the super small pads at this time as you will be using a heat gun to cure the paste which could in turn also turn other areas of paste to solder if you are not careful. Make sure to firmly hold the stencil in place during this process. Quickly and evenly remove the stencil, taking care not to mess up the solder paste that was just placed on the board. Be sure to prioritize the small ICs before moving onto the resistors and larger components.


Either dispense solder paste onto the larger pads or use a soldering iron to connect the remaining surface mount components (it is easier to solder all the components to the front side of the PCB before placing components on the back side). You can now solder any through hole components to the PCB then any components to the back side of the PCB such as the switches and battery connector. Note that it is easiest to use solder paste on the battery connector then to touch the solder paste with the tip of a hot soldering iron in order to connect the small terminals. Do not solder the transmission button at this time but every other electronic component should now be attached to the PCB.
Cut down the compression glove to the desired length, the glove must be able to reach the back of the enclosure, leaving around a half inch of material to sew the elastic cord around it. Set aside extra material to use for sewing. Mark the desired location of the transmission button, and sew it into place using the extra material. Cut enough elastic cord so that the diameter is slightly less than the glove, with some extra to tie a knot. Tie a knot and sew it into the end of the glove. 


The compression glove is now complete, and ready to be adhered to the enclosure. Gently guide the end of the glove into the notch at the back of the enclosure so the cord sits into the groove. Gluing is not required, but may be helpful to keep the glove in the notch of the enclosure. You may now feed the transmission button wire through the hole at the front of the enclosure and solder the wires onto the board. Attach the antenna to the terminal jack on the ESP-32 and position the antenna within the enclosure.

  
The hook and loop straps can be made by using no sew tape or sew on hook and loop strips. Use the leftover compression glove material or any scrap fabric you have to make the straps any desired length. The strips should be mostly loop material with the end being the hook material all facing the same direction. Sew one end of the strips onto itself or use more hook and loop material to make the end thick so it won't go through the loops on the enclosure. Feed the finished straps through the backside of the enclosure, or the side facing away from you when wearing it, and feed it over the compression glove, and into the second loop on the enclosure, you can now feed it the other way to secure the device to your arm. You may now screw on the top of the enclosure.  
  
  
## Spring 2026 Report
The 2026 Report can be found [here](<Documents/Chatter Cuff Report.pdf>) in Documents

## Acknowledgements
[Atomic14's ESP-32 Walkie-Talkie](https://github.com/atomic14/esp32-walkie-talkie)

## References
[GitHub Doc](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax#links)<br/>
[Open Source Modular Controller README](https://github.com/OSHE-Github/Open-Source-Modular-Controller/blob/main/README.md)
