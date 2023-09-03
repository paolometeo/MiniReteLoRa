/*  TX_Generic_Interrupt
 *  
 *  Generic sketch for MiniReteLoRa Transmitter
 *  Hardware                    IDE Menu board:         Connection Cable
 *  ProMicroLora                Sparkfun Pro Micro      USB micro
 *  TTGO T-Deer Pro mini LoRa   Arduino mini            FTDI 3.3 V - Black wire (GND) to the left 
 *                                                      looking at the board with the FTDI pins 
 *                                                      at the bottom and the white power plug at the top
 *  Feather 32u4 LoRa           Adafruit Feather 32u4   USB micro
 *               
 *  Setting for different boards are in Radio.h           
 *  
 *  Paolo Bonelli 16/04/2020
  */

#include "Radio.h"
#include "Sens.h"
#include "Packet.h"
#define RF95_FREQ 868.0  // LoRa Frequency
#define RF95_POW   23    // Transmitting power dBm

word ncicli =    0;
word ncicliMax = 3;
///////////////////////////////////////
byte ECHO  = 1  ;
///////////////////////////////////////
void setup() {
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
    minni.Data30002.npulse = 0;
    minni.Data30002.sPeriod = 0;   
    Transmit();
    altDelay(5000);
    attachInterrupt(digitalPinToInterrupt(interruptPin), Count, RISING);
}
//////////////////////////////////////////////////////////////////////////////
void loop() {
  ncicli++;
  Tempo = 0;
    //   This loop to hear eventually interrupts during Period millisec
  while (Tempo < Period) {
    Tempo = millis() - TimeOld;
  }
  TimeOld = millis();
  detachInterrupt(digitalPinToInterrupt(interruptPin));
  
//  After ncicliMax without interrupts, it transmits a message anyway
 if( ncicli >= ncicliMax && n == 0){
    minni.Data30002.npulse = n;
    minni.Data30002.sPeriod = 0;
    Transmit();  
    ncicli = 0;
 }
 
//  if any interrupts occurs, it transmits a message with the number of interrupts
  if(n > 0){
    minni.Data30002.npulse = n;
    minni.Data30002.sPeriod = Period;
    if(ECHO){
      Serial.print(minni.Data30002.npulse);Serial.print(" ");
      Serial.println(minni.Data30002.sPeriod);
    }
    Transmit();   //  trasmette il numero di conteggi
    ncicli = 0;
    n = 0;
  }
  attachInterrupt(digitalPinToInterrupt(interruptPin), Count, RISING);

//  Go to sleep
  if(ECHO){
     altDelay(5000);
  }else{
  
//  The radio goes to sleep
     rf95.sleep();  
     
// It goes to sleep for 16 seconds. 
     Watchdog.sleep(8000);  
     Watchdog.sleep(8000);  
  }
}
