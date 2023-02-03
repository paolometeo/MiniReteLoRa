#include <RH_RF95.h>
#include <SPI.h>
#include "Adafruit_SleepyDog.h"
#define MXbuf      50
#define MXVAR      50
/*
//   for TTGO LoRa32 SX1276  
//  Scomment the SPI.begin in RadioInit.ino
#define BOARD 1
#define RFM95_RST   14
#define RFM95_CS    18
#define RFM95_INT   26

//define the pins used by the LoRa transceiver module
#define SCK         5
#define MISO        19
#define MOSI        27
#define VBATPIN     12
#define LEDpin      13   //  for blinking
*/
/*
// uncomment setting for your board
//  for ProMicro
//  Comment the SPI.begin in RadioInit.ino
#define BOARD 2
#define RFM95_CS   10
#define RFM95_INT   7
#define VBATPIN    A9
#define LEDpin     17   //  for blinking
#define RFM95_RST   4

//define the pins used by the LoRa transceiver module
#define SCK         15
#define MISO        14
#define MOSI        16
*/
/*
//  for TTGO T-Deer Pro Mini LoRa
//  Comment the SPI.begin in RadioInit.ino
#define BOARD 3
#define RFM95_CS   10
#define RFM95_INT   2  
#define VBATPIN    A0
#define LEDpin      8   //  for blinking
#define RFM95_RST   4

//define the pins used by the LoRa transceiver module
#define SCK         13
#define MISO        12
#define MOSI        11
*/

//  for Feather 32u4
//  Comment the SPI.begin in RadioInit.ino
#define BOARD 4
#define RFM95_CS     8
#define RFM95_INT    7
#define VBATPIN      A9  
#define LEDpin      13   //  for blinking
#define RFM95_RST   4

//define the pins used by the LoRa transceiver module
#define SCK         15
#define MISO        14
#define MOSI        16


// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

uint16_t   i  = 0;
uint16_t   npacket;
byte       buf[MXbuf];
