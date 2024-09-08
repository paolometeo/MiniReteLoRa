//  THis programm works on this Hardware
//  LilyGo ESP32 LoRa T3_V1.6.1 
//  Display LCD I2C 20 x 4
//
// In the folder board_defs.h  you can comment/decomment pin setting for the board used
//
//  You can input WiFi credentials by means of your Internet Browser at the URL http://192.168.4.1/
//
//  This sketch is able to receive data from many TX node in a miniReteLoRa 
//  configuration and transmit them to the Adafruit IO server. For every TX you want to receive and 
//  decode data, you must put its data structure into Packet tab and action instruction on Action tab and 
//  Printxxx tab
//
//  This sketch can receive messages from TX adopting both the LoRa.h library or the RadioHead library
//  
//  You can choose between two frequency and two Spread Factor values.
//  You can choose also if you want to connect to a wifi network.
//  If you push the button within 5 s, The programme ask you to input 
//  credentials of WiFi network.  If you don't, it try to re-connect to the last  WiFi credentials.
//
//  AdafruitIO credentials are in the ServerConfig.h
//
//  Use Arduino IDE 2.0.3 Board setting: TTGO LoRa32-OLED
//  Oled display doesn't work in this application
//
// https://www.settorezero.com/wordpress/lora_lorawan_lilygo_ttgo_lora32_esp32/
//  https://dronebotworkshop.com/wifimanager/
//
//  modified by  Paolo Bonelli 08/12/2022
//  Version for Grassano      31/03/2023
//  Version for Test          04/07/2023
//  Version for October 2023  11/10/2023
//  Version for October 2023  17/10/2023
//  Version                   02/11/2023
//  Version for ArduinoDay and Marcacci  ..._V1 17/03/2024
//  Versione ..._V2 del 11/05/2024  con contatore messaggi arrivati
//  Version ...._V3  del 02/08/2024  It Reads 41001 message from the ProMiniLora connected to RP2024
//  Versione compatibile con ...\Ripetitore\RX_Generic_Autoconnect_Grassano_Rip_V2
//  Cambiare solo Action.ino
//  Version ...._V4 del 25/08/2024  riceve solo messaggi da TX che usano la libreria LoRa.h
/////////////////////////////////////////////////////////////////
#include <SPI.h>
// https://github.com/sandeepmistry/arduino-LoRa
// https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md
#include <LoRa.h>
#include <Wire.h>
#include "board_defs.h" // in this header I've defined the pins used by the board
#include "Radio.h"     
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include "AdafruitIO_WiFi.h"
#include "ServerConfig.h"
#include <LiquidCrystal_I2C.h>
#include <Preferences.h>
Preferences preferences;
LiquidCrystal_I2C lcd(0x27,20,4); 
#define TRIGGER_PIN 0
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY,"","");
//AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#include "Packet.h"


// Time out for connecting to WiFi
float TimePassed = 0;
float TimeOld = 0;

// Minimum time between two transmission to Adafruit for Ada
float TimePassed_Ada = 0;    
float TimeOld_Ada = 0;
float Period_Ada = 5000;    // ms
#define CONNECTION_TIMEOUT 30 // prima era 10
byte demand = 0;
byte  flgwifi = 0;
uint32_t nRestart = 0;
////////////////////////////////////
byte  TrasmettiAda = 1;   // if 0 it doesn't connect to WiFi and Adafruit
byte  nowifi = 0;
/////////////////////////////////////
void setup() {
  delay(5000);
  preferences.begin("my-app", false);
  nRestart = preferences.getUInt("nRestart", 0);
 //preferences.clear();
  //preferences.end();
  nRestart++;
  preferences.putUInt("nRestart", nRestart);
  preferences.end();
  
  pinMode(TRIGGER_PIN, INPUT_PULLUP); 

  //  Begin LCD
 // Wire.begin(OLED_SDA,OLED_SCL);
  Wire.begin(21,22);  //  Schede nuove  TTGO LoRa32 SX1276 con OLED
  delay(1000);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RX_LoRa");
 
  //  Begin Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  delay(500);
  Serial.print("nRestart ");Serial.println(nRestart);
  Serial.println("RX_LoRa");
  pinMode(LED,OUTPUT); // Green Led
  pinMode(VBAT,INPUT); // Input for Battery Voltage
   
   // Begins LoRa Module
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  lcd.setCursor(0,1);  
  lcd.print("Begin LoRa");
  lcd.setCursor(0,2);  

  // Display the two BAND
  lcd.print("BAND1 ");lcd.print(LORA_BAND1/1000000,1);
  lcd.setCursor(0,3);  
  lcd.print("BAND2 ");lcd.print(LORA_BAND2/1000000,1);
  Serial.print("LORA_BAND1 ");Serial.print(LORA_BAND1/1000000,1);
  Serial.print(" LORA_BAND2 ");Serial.println(LORA_BAND2/1000000,1);
  delay(3000);
  
  // ask for the band you want
  lcd.clear();
  lcd.print("BAND ");lcd.print(LORA_BAND1/1000000,1);
  Serial.print("Now LORA_BAND is ");Serial.println(LORA_BAND1/1000000,1);
  lcd.setCursor(0,1); 
  lcd.print("Push button toChange");
  Serial.print("Push button to Change within 5s");
  lcd.setCursor(0,2); 
  lcd.print("LORA BAND within 5s");
    demand = 0;    
    demand = PushButt(5000);  // =1 if you push button within 5 s
    Serial.print("demand ");Serial.println(demand);
    lcd.setCursor(0,3); 
    if(demand){
        if (!LoRa.begin(LORA_BAND2)){
            Serial.println("LoRa failed");
            lcd.print("LoRa failed");
            while (1);
        }
       Serial.print("You choose ");Serial.println(LORA_BAND2/1000000,1);
       lcd.print("You choose ");lcd.print(LORA_BAND2/1000000,1);
    }else{
           if (!LoRa.begin(LORA_BAND1)){
            Serial.println("LoRa failed");
            lcd.print("LoRa failed");
            while (1);
           }
       Serial.print("You choose ");Serial.println(LORA_BAND1/1000000,1);
       lcd.print("You choose ");lcd.print(LORA_BAND1/1000000,1);
    }
    delay(3000);


//  Display The two Spreading factor and ask for the SF you want
      lcd.clear();
      lcd.print("Avail.Spread.Factor");
      lcd.setCursor(0,1);  
      Serial.print("SF1 ");Serial.print(SF1);Serial.print(" SF2 ");Serial.println(SF2);
      lcd.print("SF1 ");lcd.print(SF1);lcd.print(" SF2 ");lcd.print(SF2);
      lcd.print(" Now: ");lcd.print(SF1);
      lcd.setCursor(0,2); 
      lcd.print("Push button toChange");
      Serial.print("Push button to Change within 5s");
      lcd.setCursor(0,3); 
      lcd.print("SF within 5s");
      demand = 0;    
      demand = PushButt(5000);  // =1 if you push button within 5 s
      Serial.print("demand ");Serial.println(demand);
      delay(5000);
      lcd.clear(); 
      if(demand){
         LoRa.setSpreadingFactor(SF2);           // ranges from 6-12,default 7 see API docs
         Serial.print("You choose ");Serial.println(SF2);
         lcd.print("You choose ");lcd.print(SF2);
      }else{
         LoRa.setSpreadingFactor(SF1);           // ranges from 6-12,default 7 see API docs
         Serial.print("You choose ");Serial.println(SF1);
         lcd.print("You choose ");lcd.print(SF1);
      }
    delay(3000);
    lcd.clear();
    Serial.println("LoRa OK");
    lcd.print("LoRa OK!");
    delay(3000);

/*
   See Air Calculator by https://www.thethingsnetwork.org/airtime-calculator
    LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs
    LoRa.setSignalBandwidth(125000);
     LoRa.setCodingRate4(8);
*/

//  LoRa.setTxPower(int level, int outputPin)  // max level 20
//  LoRa.setTxPower(int level, int outputPin = PA_OUTPUT_PA_BOOST_PIN);  // ?

  //  Choose if you want WiFi
  lcd.clear();
  lcd.print("Don't want WiFi ?");
  lcd.setCursor(0,1); 
  lcd.print("Push button if Yes");
  lcd.setCursor(0,2); 
  lcd.print("within 5s");
    demand = 0;    
    demand = PushButt(5000);  // =1 if you push button within 5 s
    Serial.print("demand ");Serial.println(demand);
    lcd.setCursor(0,3); 
    if(demand){
       nowifi = 1;
       TrasmettiAda = 0;
       lcd.print("You choose No WiFi");
       Serial.println("You choose No WiFi");
    }else{
      nowifi = 0;
      TrasmettiAda = 1;
      lcd.print("You choose WiFi");
      Serial.println("You choose WiFi");
   }
   delay(3000);
//
  if(TrasmettiAda  && !nowifi){
    
//  Begin WiFi connection
      Serial.println("Inizio Collegamento WiFi");
      WiFi.mode(WIFI_STA);
     Serial.print("Connecting to WiFi, WiFI_STA ");
      Serial.println(WIFI_STA);
      Serial.println();
      Serial.print("Wait for WiFi... ");Serial.println(WIFI_SSID);
      lcd.clear();  
      lcd.print("Connecting to WiFi");
      delay(3000);
      
  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
      WiFiManager wm;
    wm.setConfigPortalTimeout(120);  // 120 secondi prima era 60 secondi
// reset settings - wipe stored credentials for testing
 // these are stored by the esp library
 //       String ssdi = wm.getDefaultAPName();
 //      Serial.println(ssdi);       

    Serial.println("Push button for input within 5 sec");
    lcd.clear();
    lcd.print("Push button to enter");
    lcd.setCursor(0,1); 
    lcd.print("credential within 5s");
     demand = 0;    
     demand =    PushButt(5000);  // =1 if you push button within 5 s
    Serial.print("demand ");Serial.println(demand);
    lcd.setCursor(0,2); 
    if(demand){
      wm.resetSettings();
      lcd.print("Connecting to ESP32");
    }else{
      lcd.print("Connecting old SSID");
    }
   
   // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "ESP32"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result
    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    //    put a password for AutoconnectAP
    // res = wm.autoConnect("AutoConnectAP", "password"); // with password
       Serial.println(" chiamo autoconnect");
       res = wm.autoConnect("ESP32AP"); // with no password
       Serial.println(WIFI_SSID);
       Serial.print(" res ");Serial.println(res);
       lcd.setCursor(0,3); 
       lcd.print("Wait for WiFi");
       delay(3000);
       int timeout_counter = 0;
       while(WiFi.status() != WL_CONNECTED){
        delay(200);
        timeout_counter++;
        if(timeout_counter >= CONNECTION_TIMEOUT*5){
          Serial.println(" ESP-restart ");
          ESP.restart();
        }
       }
       delay(3000);
       if(!res) {
          Serial.println("Failed to connect");
          lcd.print("Failed to connect");       
          flgwifi = 0;
          TrasmettiAda = 0;       
       }else {
        //if you get here you have connected to the WiFi    
          Serial.println("connected...yeey :)");
          lcd.setCursor(0,3);
          lcd.print("Connected!!        ");     
          flgwifi = 1;    
       }
       Serial.println(TrasmettiAda,DEC);
       delay(3000);
    }  //  You haven't choosen WiFi
    else{
    lcd.setCursor(0,1); 
    }
  Serial.print("Trasmetti_Ada ");Serial.println(TrasmettiAda,DEC);
  Serial.print("nowifi ");Serial.println(nowifi,DEC);
  delay(3000);

// Connecting to Adafruit
 if(TrasmettiAda && !nowifi){  
  lcd.clear();
  lcd.print("Connecting Adafruit");
  lcd.setCursor(0,1);
  Serial.print("Connecting to Adafruit IO with User:"); 
  Serial.print(IO_USERNAME);Serial.print(" ");Serial.println(IO_KEY);
  io.connect();    
  TimeOld = millis();
  while ((io.status() < AIO_CONNECTED)){
      Serial.println(io.status());
      Serial.println(io.statusText());
      TimePassed = millis() - TimeOld;
      if(TimePassed > 20000){
         TrasmettiAda = 0; 
         break;
      }
      delay(500);
    }
    if(TrasmettiAda){
  Serial.print("Connecting to Adafruit IO with User:"); 
  Serial.print(IO_USERNAME);Serial.print(" ");Serial.println(IO_KEY);
       lcd.print("Connected!!        ");
       lcd.setCursor(0,2);
       lcd.print(IO_USERNAME);       
    }else{
      Serial.println("Failed to connect to Adafruit");
      lcd.print("No Adafruit Server");
      ESP.restart();
    }      
//  print on display
         Serial.print("IP address: ");
         Serial.println(WiFi.localIP());         
         lcd.setCursor(0,3);      
         lcd.print(WiFi.localIP());   
         Serial.print(" io.status ");
 }
}
//////////////////////////////////////////////// 
void loop() {

  Roger = Receive();  
  if(Roger){   
   if(!nowifi){
      if(TrasmettiAda){
          int pippo =   io.run();
          if(pippo != 21){
              Serial.print("statusText ");Serial.println(io.statusText());
              lcd.setCursor(0,2);
              lcd.print("No connection");
              lcd.setCursor(0,3);
              lcd.print("Restarting...");
              delay(3000);
              ESP.restart();
              delay(1000);
          }
        }    
      }
     Action(); 
  }    
    Roger = 0;
  }
 // delay(1);   // Pay attention!  Too long a delay can cause the card to become deaf to some messages 
