/*  TX_general
 *  
 *  Generic sketch for MiniReteLoRa Transmitter
 *  Hardware                    IDE Menu board:         Connection Cable
 *  ProMicroLora                Sparkfun Pro Micro      USB micro
 *  TTGO T-Deer Pro mini LoRa   Arduino mini            FTDI 3.3 V - Black wire (GND) to the left 
 *                                                      looking at the board with the FTDI pins 
 *                                                      at the bottom and the white power plug at the top
 *       available pins: D0, D1, D3,  D5, D7, A1, A2, A3, A4, A5, A6, A7    
 *                                                  
 *  Feather 32u4 LoRa           Adafruit Feather 32u4   USB micro
 *               
 *  Setting for different boards are in Radio.h           
 *  
 *  Paolo Bonelli 18/04/2021
  */

#include "Radio.h"
#include "Sens.h"
#include "Packet.h"
#define RF95_FREQ 868.0  // LoRa Frequency
#define RF95_POW   23    // Transmitting power dBm
word ncicli =    0;
word ncicliMax = 10;     // Number of loop cycles after which it transmits
byte ECHO  = 0 ;
void setup() {
  //  Initializing the radio
    RadioInit();
    Serial.println(F("TX_Generic.ino"));
    rf95.setFrequency(RF95_FREQ);
    if (ECHO) {
      Serial.print(F("Set Freq to: ")); Serial.println(RF95_FREQ);
    }
//  Set transmission Power
    rf95.setTxPower(RF95_POW, false);
    if (ECHO) {
    Serial.print(F("Set Power to: ")); Serial.println(RF95_POW);
  }  
  SensInit();
  
//   First transmission with all the variables at 0
    minni.Data30003.Humi = 0;
    minni.Data30003.Temp = 0;   
    Transmit();
    altDelay(5000);
}

void loop() {
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
     rf95.sleep();  
// It goes to sleep for 8 seconds. 
     Watchdog.sleep(8000);  
  }
}
