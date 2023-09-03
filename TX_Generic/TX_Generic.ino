/*  TX_Generic
 *  
 *  Generic sketch for MiniReteLoRa Transmitter
 *  Hardware                    IDE Menu board:         Connection Cable

 *  ProMicroLora                Sparkfun Pro Micro      USB micro
 *  TTGO T-Deer Pro mini LoRa   Arduino mini            FTDI Power 5V Signal 3V3- Black wire (GND) to the left 
 *                                                      looking at the board with the FTDI pins 
 *                                                      at the bottom and the white power plug at the top
 *       available pins: D0, D1, D3,  D5, D7, A1, A2, A3, A4, A5, A6, A7    
 *                                                  
 *  Feather 32u4 LoRa           Adafruit Feather 32u4   USB micro
 *  Pro Mini LoRa               Arduino Pro or ProMini  FTDI with 3V3 Adapter Power 3V3
*                               8 MHz, 3V3
 *               
 *  Setting for different boards are in Radio.h           
 *  
 *  Paolo Bonelli 16/04/2020
    Paolo Bonelli 01/09/2023
*/

#include "Radio.h"
#include "Sens.h"
#include "Packet.h"
#include <avr/wdt.h>
#define RF95_FREQ 868.0  // LoRa Frequency
#define RF95_POW   23    // Transmitting power dBm

word ncicli =    0;
word ncicliMax = 1;
///////////////////////////////////////
byte ECHO  = 1 ;
///////////////////////////////////////
void setup() {
   wdt_disable();

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
  wdt_enable(WDTO_4S);    
  SensInit();
  
//   First transmission with all the variables at 0
    minni.Data30003.Humi = 0;
    minni.Data30003.Temp = 0;   
    Transmit();
    altDelay(5000);
}
//////////////////////////////////////////////////////////////////////////////
void loop() {
  wdt_enable(WDTO_4S);    
  ncicli++;
  if(ncicli >= ncicliMax){
   ReadSensor();

// Transmit data
    Transmit();
    ncicli = 0;
  }
 
  if(ECHO){
     altDelay(5000);
  }else{
  
//  The radio goes to sleep
     wdt_disable();
     rf95.sleep();  
     Watchdog.sleep(2000);  
  }
}
