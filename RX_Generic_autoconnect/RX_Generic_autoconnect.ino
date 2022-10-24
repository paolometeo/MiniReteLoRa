/* RX_Generic_Autoconnect
*  This Programm is for the gateway of the MiniReteLoRa.
*  Hardware: 
   ESP32 LoRa T3_V1.6.1 by LilyGo 
   TTGO LoRa32 SX1276
   
 * This is an Adafruit feed subscribe  that uses
 * WiFiManager to handle setup of WiFi credentials and connecting
 * to the network instead of defining the WiFI SSID and password
 * explicitly in the code.
 *
 * In addition, the programm allows you to enter your Adafruit IO username and key
 * as customer parameters in WiFiManager so that they do not need to be coded into
 * the sketch.
 * 
 * This is useful if you want to create projects and share them with others that
 * may use them on a different WiFi network and use a different Adafruit IO account
 * for IOT integrations such as collecting sensor data or voice command integration via
 * IFFT.
 *
 * When the  ESP32 microcontroller starts, join the "WiFi Setup" SSID and you should be presented
 * with the config portal.  If the config portal does not automatically start you
 * can browse to http://192.168.4.1 to access it
 *
 * Select the SSID and enter the password for WiFi Access in the config portal.
 * Enter your Adafruit IO username and key in the config portal and select "Save". *
 * Brad Black - 2022
*  Paolo Bonelli  23/10/2022 

//
//  IDE Board setting: TTGO LoRa32-OLED
//  For test use this Adafruit accout:  outdoorsensing - aio_EfFI35RI51ofBXZ3tH2lN9gQqwPL
// 
*/
/////////////////////////////////////////////////////////////////
//#include <SPI.h>
#include <LoRa.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <Wire.h>
// Library for OLED display
//  OLED 128 x 64
#include <Adafruit_SSD1306.h>  //
#include "board_defs.h" // in this header I've defined the pins used by the module LILYGO® TTGO LoRa32 V2.1_1.6
#include "Radio.h"     
#include "Packet.h"
//#include "ServerConfig.h"
#include "AdafruitIO_WiFi.h"

char IO_USERNAME[64] = "";
char IO_KEY[64] = "";
byte  flgwifi = 0;
float TimeOld = 0;
float TimePassed = 0;

 //  Each character is 10 (height) x 6 (width)
  //  128 x 64 means 5 row x 21 char

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST);

static uint8_t objStorage[sizeof(AdafruitIO_WiFi)]; // RAM for the object

AdafruitIO_WiFi *io;                              // a pointer to the object, once it's constructed
 

// create WiFiManager object and define our custom parameters

WiFiManager wifiManager;
WiFiManagerParameter custom_IO_USERNAME("iouser", "Adafruit IO Username", IO_USERNAME, 60);
WiFiManagerParameter custom_IO_KEY("iokey", "Adafruit IO Key", IO_KEY, 60);

 

/////////////////////////////////////////////////////
void setup() {
  delay(5000);
  pinMode(LED,OUTPUT); // Green Led
  pinMode(VBAT,INPUT); // Input for Battery Voltage

    // Begins OLED
  //reset OLED display via software
  
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("RX_LoRa_autoconnect");
  display.display();
  
//  Begin Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  delay(500);
  Serial.println("RX_Generic_Autoconnect");
 
  // Begins LoRa Module
//SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  
  if (!LoRa.begin(LORA_BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.print("LoRa OK, Freq: ");Serial.println(LORA_BAND/1000000,1);
  display.setCursor(0,11);
  display.print("LoRa OK ");display.print(LORA_BAND/1000000,1);
  display.display();
  delay(2000);
  display.display();

//WiFi  and Adafruit connection
  AutoConnection();
 
//  print on display
     if(flgwifi){
         Serial.println("");
         Serial.println("WiFi connected");
         Serial.println("IP address: ");
         Serial.println(WiFi.localIP());
//
         display.setCursor(0,22);
         display.print("LocalIP:"); display.print(WiFi.localIP());
         display.setCursor(0,33);
         display.print("Connected Adafruit"); 
         display.setCursor(0,44);
         display.print(IO_USERNAME);         
         display.display();
     }  
     
  int mV = Battery();
  Serial.print(" Batteria RX ");Serial.println(mV);  
  display.setCursor(0,55);  
  display.print("Batt.RX ");display.print(mV);
  display.display();

  
}
//////////////////////////////////////////////// 
void loop() {
  io->run();
  byte Roger = 0;
  Roger = Receive();  
  if(Roger){
//  Identification and re-transmission 
         if (ID_TX == ID0){
                AdafruitIO_Feed *Temp = io->feed("Temp");
                AdafruitIO_Feed *Humi = io->feed("Humi");
                Temp ->    save(minni.Data30003.Temp);
                Humi ->    save(minni.Data30003.Humi);
                Print30003();
              
         }else if(ID_TX == ID1){
               AdafruitIO_Feed *Tair = io->feed("Tair");
               AdafruitIO_Feed *Umid = io->feed("Umid");
               AdafruitIO_Feed *Light = io->feed("Light");           
               Tair->    save(minni.Data50000.Tair);
               Umid->    save(minni.Data50000.Umid);
               Light->    save(minni.Data50000.Light);
               Print50000();
                
         }else if(ID_TX == ID2){
               AdafruitIO_Feed *npulse = io->feed("npulse");
               AdafruitIO_Feed *sPeriod = io->feed("sPeriod");
               npulse->    save(minni.Data30002.npulse);
               sPeriod->    save(minni.Data30002.sPeriod);
               Print30002();
         }else{
               Serial.println(" ID_TX not permitted ");
         }
    Roger = 0;
  }
}
