#include <RH_RF95.h>
#include "Adafruit_SleepyDog.h"
#define MXbuf      50
#define MXVAR      50
#define RFM95_RST   4

// uncomment setting for your board
/*
//  for ProMicro
#define RFM95_CS   10
#define RFM95_INT   7
#define VBATPIN    A9
#define LEDpin     17   //  for blinking
*/

//  for TTGO
#define RFM95_CS   10
#define RFM95_INT   2  
#define VBATPIN    A0
#define LEDpin      8   //  for blinking
/*
//  for Feather 32u4
#define RFM95_CS  8
#define RFM95_INT 7
#define VBATPIN   A9  
#define LEDpin    13   //  for blinking
*/

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

uint16_t   i  = 0;
uint16_t   npacket;
byte       buf[MXbuf];
