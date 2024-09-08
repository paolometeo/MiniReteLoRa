#include <SPI.h>              // include libraries
#include <LoRa.h>
//#include "Adafruit_SleepyDog.h"
#define MXbuf      50
#define MXVAR      50

// uncomment setting for your board
/*
//  for ProMicro 
#define RFM95_CS   10
#define RFM95_INT   7
#define VBATPIN    A9
#define LEDpin     17   //  for blinking
#define RFM95_RST   4
*/
/*
//for TTGO
#define RFM95_CS   10
#define RFM95_INT   2  
#define VBATPIN    A0
#define LEDpin      8   //  for blinking
#define RFM95_RST   4
*/
/*
//  for Feather 32u4
#define RFM95_CS  8
#define RFM95_INT 7
#define VBATPIN   A9  
#define LEDpin    13   //  for blinking: LOW when on
#define RFM95_RST   4
*/

//  for Pro Mini
#define RFM95_CS   10
#define RFM95_INT   2
#define VBATPIN    A3
#define LEDpin      8   //  for blinking
#define RFM95_RST   4


// Singleton instance of the radio driver
//RH_RF95 rf95(RFM95_CS, RFM95_INT);

uint16_t   npacket = 0;
byte       buf[MXbuf];
