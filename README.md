# LilyGo-T-Relay-S3-Blynk
A way to use Blynk App on LilyGo-T-Relay S3 Board

# Arduino IDE Board Settings
Board -> ESP32S3 Dev Module  
USB CDC On Boot -> Enable  
CPU Frequency -> 240MHz  
USB DFU On Boot -> Disable  
Flash Mode -> QIO 80MHz  
Flash Size -> 16MB(128Mb)  
USB Firmware MSC On Boot -> Disable  
PSRAM -> OPI PSRAM  
Partition Scheme -> 16M Flash(3MB APP/9.9MB FATFS)  
USB Mode -> Hardware CDC and JIAG  
Upload Mode -> UART0/Hardware CDC  
Upload Speed -> 921600  

# Board Tips
1.⚠T-Relay uses Octal SPI Flash, so GPIO35 ~ GPIO37 are not available, please do not use these IOs in the software.  
2.⚠T-Relay 3v3* The maximum external current allowed is 500mA, please do not exceed this supply current.  
3.⚠T-Relay 5V Pin The maximum allowable current is 3000mA, ESP32S3 and other external components require nearly 800mA current, so please do not connect external components greater than 2000mA.  
4.⚠T-Relay The maximum allowable current for electric shock on relay pins is 10A load current, please do not connect load devices exceeding 2500W.  
5.⚠If an external relay load greater than 48V is connected, please power off the main board and connected equipment first to prevent electric shock.  
6.⚠T-Relay is a serial-to-parallel design for 74HC595, allowing multiple T-Relay sub-boards to be connected, but please note that due to the design of the power supply of the main board, it is currently recommended that cascaded devices not More than 3 relay sub-boards, cascading three sub-boards, the power supply of the main board will be hot, which is normal, please do not touch it with your hands to prevent burns. If you work for a long time, it is recommended to paste a heat sink on the inductor of the power supply to assist the main board to dissipate heat.  
7.⚠ The DS18B20 sensor interface is reserved by default, and there is no such sensor by default.  
8.External reserved expansion screen interface Support TFT Module Link , Relay-S3 default design size is 2.4 inches.  
9.The board uses USB as the JTAG upload port. When printing serial port information on USB_CDC_ON_BOOT configuration needs to be turned on. If the port cannot be found when uploading the program or the USB has been used for other functions, the port does not appear. Please enter the upload mode manually.  
- Connect the board via the USB cable  
  1.Press and hold the BOOT button , While still pressing the BOOT button, press RST.  
  2.Release the RST.  
  3.Release the BOOT button.  
  4.Upload sketch.
  
# Shift Registers Usage:

| Shift register | DATA | CLOCK | LATCH |
|----------------|------|-------|-------|
| GPIO           | 7    | 5     | 6     |


| Relay/LED    | Register Value    |
|--------------|-------------------|
| 1            | 0b10000000        |
| 2            | 0b01000000        |
| 3            | 0b00100000        |
| 4            | 0b00010000        |
| 5            | 0b00001000        |
| 6            | 0b00000100        |
| Green LED    | 0b00000010        |
| Red LED      | 0b00000001        |

Check line 63 for usage example.
# Clean Registers Function
At line 33 we have a function called clearRegisters. It was implemented because the board turns off and on with register values ​​that are different from what they were when turned off. I believe it is some electronic noise on the board or some design error.  If you need to maintain the last state of the relays when the board turns off, consider saving the states in EEPROM.
# Blynk Settings
These lines need to be filled with Blynk Project API info and WiFi SSID & Password:
```C++
  #define BLYNK_TEMPLATE_ID ""
  #define BLYNK_TEMPLATE_NAME ""
  #define BLYNK_AUTH_TOKEN "" 

  char ssid[] = "";
  char pass[] = "";
  
