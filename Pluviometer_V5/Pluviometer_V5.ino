/*  Pluviometer_V4
/*
 * Hardware:  TTGO T-Deer ProMini LoRa, Rain Gauge Davis 
 * 
 * The MCU counts the number of interrupts and transmits it every a certain amount of time
 * if the number is larger than a threshold the transmitting period decreases.
 * 
 *    Wiring
 *         10 K
 *    ____/\/\/\______ +3.3V   pull-up resistor
 *    |_______________  PluvioPin   
 *  __|__         |
 *  _____ 0.1 uF  / Rain gauge bucket  
 *    |           |
 *   _|_         _|_
 *   ///         /// GND
 
 *   TTGO T-Deer Pro mini LoRa   Arduino mini            FTDI 3.3 V - Black wire (GND) to the left 
 *                                                      looking at the board with the FTDI pins 
 *                                                      at the bottom and the white power plug at the top
 *               
 *   IDE version: 1.8.19
 *  Setting for different boards are in Radio.h           
 * Pioggia moderata 10 mm/h; pioggia violenta 100 mm/h (500 conteggi/h o 8 cont/m) 
 *  Paolo Bonelli 22/11/2022
  */

#include "Radio.h"
#include "Sens.h"
#include "Packet.h"
#define  RF95_FREQ 868.0  // LoRa Frequency
#define  RF95_POW   23    // Transmitting power dBm
#include <avr/wdt.h>
  int  n =      0;
  int  n1 =     1;          // threshold of count 
  long Period = 174000;  // ms during the bucket count  (3 min)
  int  TimeSleep = 0;
  int  ncicli =    0;
  int  ncicliMax = 30;  // 
///////////////////////////////////////
byte ECHO  = 0  ;   //Echo must be 0 when using sleep. 
// There is conflict between Serial.print and sleep
///////////////////////////////////////
void setup() {
    if(ECHO){
      while (!Serial);  
      Serial.begin(57600);
      altDelay(100);
      Serial.println("Pluviometer_V5.ino");
     }
  //  Initializing the radio
    RadioInit();
    rf95.setFrequency(RF95_FREQ);
    if (ECHO) {
      Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
    }
//  Set transmission Power
    rf95.setTxPower(RF95_POW, false);
    if (ECHO) {
    Serial.print("Set Power to: "); Serial.println(RF95_POW);
    }  
   
     SensInit();
  
//   First transmission with all the variables at 0
    minni.Data12140.npulse = 0;
    minni.Data12140.Per =    0;  
    minni.Data12140.Irain =  0;
    minni.Data12140.WetnessA =0;
    minni.Data12140.WetnessB =0;
    Transmit();
    ncicli = 0;
//    wdt_enable(WDTO_8S);      
    altDelay(5000);
}
//////////////////////////////////////////////////////////////////////////////
void loop() {

  if(ECHO)Serial.println("sveglio");
  ncicli++;
  wdt_enable(WDTO_8S);      
  TimeSleep = 8000;
  ReadWet();
  if(ncicli > ncicliMax){
    if(ECHO)Serial.println(ncicli);
    minni.Data12140.npulse = 0;
    minni.Data12140.Per = Period/1000;
    minni.Data12140.Irain = 0;
    Transmit();
    ncicli = 0;
  }
  if(WetFlg){
   if(ECHO){
      Serial.println("ReadPluvio");
   }
   ReadPluvio();
   if(ECHO){
      Serial.print("n = ");Serial.println(n);
   }
   minni.Data12140.Per = Period/1000;
   float Frain = PluvioFactor*float(n)*60/float(minni.Data12140.Per);  // 0.1 mm/min
   if(ECHO){
          Serial.print("Frain ");Serial.println(Frain,4);
   }
   minni.Data12140.Irain = Nword(Frain);     
   Transmit();
   ncicli = 0;
   if(n < n1){
     TimeSleep = 7000;
   }
   if(n >= n1){
    TimeSleep = 10;
   }   
   n = 0;
  }
  if(ECHO){
    altDelay(TimeSleep);
  }else{
  wdt_disable(); 
  rf95.sleep();
  Watchdog.sleep(TimeSleep);  
  }
}
