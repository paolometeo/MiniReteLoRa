//  Board ESP32 LoRa T3_V1.6.1 by LilyGo 
//  This sketch is able to receive data from many TX node in a miniReteLoRa 
//  configuration and transmit them to the Adafruit IO server
//  It restarts in the case WiFi connection go down
//
// https://www.settorezero.com/wordpress/lora_lorawan_lilygo_ttgo_lora32_esp32/
//  modified by  Paolo Bonelli 31/01/2022
//
//  IDE Board setting: TTGO LoRa32-OLED (V1)
/////////////////////////////////////////////////////////////////
//#include <SPI.h>
#include <LoRa.h>
// Library for OLED display
//  OLED 128 x 64
#include <SSD1306Wire.h>
#include "board_defs.h" // in this header I've defined the pins used by the module LILYGO® TTGO LoRa32 V2.1_1.6
#include "Radio.h"     
#include "ServerConfig.h"
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#include "Packet.h"
byte  flgwifi = 0;
byte  TrasmettiAda = 1;
float TimeOld = 0;
float TimePassed = 0;
int   mm = 0;
SSD1306Wire display(OLED_ADDRESS, OLED_SDA, OLED_SCL);

/////////////////////////////////////////////////////
void setup() {
  delay(5000);
  pinMode(LED,OUTPUT); // Green Led
  pinMode(VBAT,INPUT); // Input for Battery Voltage

    // Begins OLED
  display.init();
  display.flipScreenVertically(); 
  display.clear();
  delay(100); 
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //  Each character is 10 (height) x 6 (width)
  //  128 x 64 means 5 row x 21 char
  display.setFont(ArialMT_Plain_10);
  
//  Begin Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  delay(500);
  Serial.println("RX_Generic");

  // Begins LoRa Module
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  if (!LoRa.begin(LORA_BAND)){
    display.drawString(0,0,"NO LoRa");
    Serial.println("LoRa failed");
    while (1);
  }  
  Serial.println("LoRa OK");
  display.drawString(0,0,"LoRa OK");
  display.display();
  
//  Begin WiFi connection
  if(TrasmettiAda){
     Serial.print("Connecting to WiFi");
     WiFi.mode(WIFI_STA);
     Serial.println(WIFI_STA);
     Serial.println();
     Serial.print("Wait for WiFi... ");Serial.println(WIFI_SSID);
     io.connect();
     TimeOld = millis();
     flgwifi = 1;  
     while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        TimePassed = millis() - TimeOld;
        if(TimePassed > 20000){
           flgwifi = 0;  // no WiFi 
           break;
        }
        delay(500);
     }
     
//  print on display
     if(flgwifi){
         Serial.println("");
         Serial.println("WiFi connected");
         Serial.println("IP address: ");
         Serial.println(WiFi.localIP());
         display.drawString(64,0,"WiFi OK");
         display.drawString(0,11,"Local IP: " + WiFi.localIP().toString());
         display.display();
         byte ioStatus = io.status();
         delay(1000);
         Serial.print(" io.status ");
         Serial.print(ioStatus);  //  11  quando non riesce ad entrare in Adafruit, 21 invece si
         if(ioStatus == 11){
             TrasmettiAda = 0;
             Serial.println(" Adafruit not connected ");
             display.drawString(0,22,"No Server connected" );
             display.display();
         }
         Serial.print(" "); Serial.println(AIO_CONNECTED); //  21 lo stesso
    }else{
         TrasmettiAda = 0;
         Serial.println("No WiFi");
         display.drawString(0,22,"No WiFi" );
         display.display();
    }
  }
  int mV = Battery();
  Serial.print(" Batteria RX ");Serial.println(mV);  
  display.drawString(0,33,"Batt.RX " + String(mV) + "mV");
  display.display();
}
//////////////////////////////////////////////// 
void loop() {

// check if connection is alive, otherwise it restarts
  if(TrasmettiAda){
   int pippo =   io.run();
   if(pippo != 21){
    ESP.restart();
    delay(1000);
   }
 }    
  byte Roger = 0;
  Roger = Receive();  
  if(Roger){
    Action();
    Roger = 0;
  }
  delay(10);
}
