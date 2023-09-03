/*
 * Programm for the Ripetitor of the Prova_Regolatore_V5
 * 
 * Arduino IDE version 1.8.19
 * Board: TTGO Arduino Mini
 * 
 * Paolo Bonelli 24/08/2023
 */

#include "Radio.h"
#include <Wire.h>
#include "Packet.h"
#define  RF95_FREQ     868.1  // LoRa Frequency
#define  RF95_FREQ_RIP 868.2  // LoRa Frequency
#define  RF95_POW   23    // Transmitting power dBm
#include <avr/wdt.h>
#define ECHO 0
//int ncicliMax = 10;   //  period del TX
int ncicliMax    = 9;      //  period of the RIP sleep
int ncicliMaxRIP = 31;  //  period of the RIP status message
int TimeSleep    = 2000;  //   as TX
int ncicli       = 0;
int ncicliRIP    = 0;
byte Roger       = 0;
long TimePassed  = 0;
long TimeOld     = 0;
long TimeOut     = 180000;  // 2 min

void setup() {
    if(ECHO){
      while (!Serial);  
      Serial.begin(57600);
      altDelay(100);
      Serial.println("RepeaterGeneric.ino");
     }
  //  Initializing the radio
    RadioInit();
    rf95.setFrequency(RF95_FREQ);
    if (ECHO) {
      Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
    }
    rf95.setTxPower(RF95_POW, false);
    if (ECHO) {
          Serial.print("Set Power to: "); Serial.println(RF95_POW);
          Serial.println("I am waiting for the first message");
    }  
    
    // Wait for a message
    TimeOld = millis();
    TimePassed = 0;
    while(!Roger && TimePassed < TimeOut){
      Roger = Receive(); 
      TimePassed = millis()-TimeOld;
    } 

    //  No messages from TX, it transmits a message about the RIP status
    if(TimePassed >= TimeOut){
     rf95.setFrequency(RF95_FREQ_RIP);
     if (ECHO) {
          Serial.print("Set Freq to: "); Serial.println(RF95_FREQ_RIP);
     }
     minni.Data12129.stato = 2;  
     TransmitRIP();
     minni.Data12129.stato = 0;
    }
    if(Roger){
      if(ECHO){
        Serial.println(" I received a message");
      }
      Action();
      Roger = 0;
    }
    Serial.println(" Finish setup");
}
////////////////////////////////7
void loop() {
  ncicli++;
  ncicliRIP++;
  if(ECHO){
    Serial.print(" ncicli ");Serial.print(ncicli);
    Serial.print("  ncicliRIP ");Serial.println(ncicliRIP);
  }
  wdt_enable(WDTO_4S);        
  if(ncicli >= ncicliMax){
     ncicli = 0;

    // Wait a message
    rf95.setFrequency(RF95_FREQ);
    if(ECHO){
      Serial.println();
      Serial.println(" I am waiting for a message ");
      Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
    }
    Roger = 0;
    TimePassed = 0;
    TimeOld = millis();
    while(!Roger && TimePassed < TimeOut){
      Roger = Receive(); 
      TimePassed = millis()-TimeOld;
      altDelay(1);
    } 
    if(TimePassed >= TimeOut){

      //  It transmit a message about the RIP status
        rf95.setFrequency(RF95_FREQ_RIP);
        if (ECHO) {
          Serial.print("Set Freq to: "); Serial.println(RF95_FREQ_RIP);
        }
        minni.Data12129.stato = 3;  
        TransmitRIP();
        minni.Data12129.stato = 0;
    }
    if(Roger){
      if(ECHO){
        Serial.println(" I received a message");
      }
      Action();
      Roger = 0;
    }
  }
  
//   It transmits a message on the RIP status anyway after ncicliMaxRIP
  if(ncicliRIP >= ncicliMaxRIP){
     ncicliRIP = 0;
     minni.Data12129.stato = 1;   // all is OK
     rf95.setFrequency(RF95_FREQ_RIP);
     if (ECHO) {
          Serial.print("Set Freq to: "); Serial.println(RF95_FREQ_RIP);
     }
     TransmitRIP();
     minni.Data12129.stato = 0;
  }
  
  if(ECHO){
    altDelay(TimeSleep);
  }else{
  wdt_disable(); 
  rf95.sleep();
  Watchdog.sleep(TimeSleep);  
  }
}
