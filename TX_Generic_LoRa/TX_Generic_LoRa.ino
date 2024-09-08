/*
/*  TX_general_LoRa
 *  
 *  Generic sketch for MiniReteLoRa Transmitter with LoRa library
 *   Compiler IDE: 1.8.19
 
 *  Hardware                         IDE Menu board:               Connection Cable
 *  _____________________________________________________________________________________
 *  >ProMicroLora                    Sparkfun Pro Micro             USB micro
 *  >TTGO T-Deer Pro mini LoRa       Arduino mini                   FTDI 5V  - Black wire (GND) to the left 
 *                                                                  looking at the board with the FTDI pins 
 *                                                                  at the bottom and the white power plug at the top
 *                                                                  available pins: D0, D1, D3,  D5, D7, A1, A2, A3, A4, A5, A6, A7    
 *                                                  
 *  >Feather 32u4 LoRa               Adafruit Feather 32u4          USB micro
 *  >Arduino Pro Mini with LoRa     Arduino Pro o Pro Mini         USB FTDI 3V3
 *                                   8 MHz 3.3 V
 *               
 *  Setting for different boards are in Radio.h           
 *  
 *  Paolo Bonelli 16/04/2020
 *  Paolo Bonelli 24/04/2023
 *  Paolo Bonelli 24/08/2024  Usa la Libreria LoRa.h  per cambiare lo Spreading Factor
 *                                     
 *   
 */
#include "Radio.h"
#include "Sens.h"
#include "Packet.h"
#include <Wire.h>
//#include <avr/wdt.h>
#include "LowPower.h"

////////////////////////////////////////////////////////////    
byte  ECHO = 1;          // = 1 it's test mode and it prints on serial monitor; 
//                          = 0 it's operative mode with sleep and it doesn't print
///////////////////////////////////////////////////////////
uint16_t ncicli =    0;
uint16_t ncicliMax = 3;  // 30 s tra un messaggio e l'altro
#define RF95_FREQ 868E6    // LoRa Frequency
#define RF95_POW   20      // Transmitting power dBm
#define SF 7
//
void setup() {  
//    wdt_disable();
//    wdt_enable(WDTO_8S);    
    if(ECHO){
      Serial.begin(57600);
      altDelay(100);
    }
    //  Initializing the radio
    RadioInit();
   //   Initializing the sensor  
  SensInit();
  if(ECHO)Serial.println(F("TX_Generic_LoRa"));
  ncicli = 0;
  npacket = 0;
  ncicliMax = 3;  
}
/////////////////////////////////////////////////////////
void loop() {
//  wdt_enable(WDTO_8S);    
  ncicli++;
  
//  Test wdt_reset
//  if(npacket == 3)delay(10000);
  
  if(ncicli >= ncicliMax){
       ncicli = 0;             
//  Put here the instructions to get the values of your variable
    ReadSensor();
//  Transmit data
    Transmit();
  }
  if(ECHO){
     altDelay(8000);
  }else{
  
//  The radio goes to sleep
//     wdt_disable();   //  incompatibile con  libreria LoRa
//     rf95.sleep();  
// The ProMicro goes to sleep for 1 second. 
     LoRa.sleep();
//     Watchdog.sleep(8000);  
/*
  SLEEP_15MS,
  SLEEP_30MS,
  SLEEP_60MS,
  SLEEP_120MS,
  SLEEP_250MS,
  SLEEP_500MS,
  SLEEP_1S,
  SLEEP_2S,
  SLEEP_4S,
  SLEEP_8S,
  SLEEP_FOREVER
 */
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}
