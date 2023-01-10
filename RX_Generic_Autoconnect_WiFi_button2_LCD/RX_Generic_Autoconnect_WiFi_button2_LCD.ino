//  THis programm works on this Hardware
//  LilyGo ESP32 LoRa T3_V1.6.1 
//  Display LCD I2C 20 x 4
//
// In the folder board_defs.h  you can comment/decomment pin setting for the board used
//
//  You can input WiFi credentials by means of your Internet Browser at the URL http://192.168.4.1/
//
//  This sketch is able to receive data from many TX node in a miniReteLoRa 
//  configuration and transmit them to the Adafruit IO server
//  
//  If you push the button, The programme ask you to input 
//  credentials of WiFi network.
//  If you don't, it try to re-connect to the last  WiFi credentials.
//
//  AdafruitIO credentials are in the ServerConfig.h
//
//  Use Arduino IDE 2.0.3 Board setting: TTGO LoRa32-OLED
//  OLed display doesn't work in this application
//
// https://www.settorezero.com/wordpress/lora_lorawan_lilygo_ttgo_lora32_esp32/
//  https://dronebotworkshop.com/wifimanager/
//
//  modified by  Paolo Bonelli 08/12/2022
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
LiquidCrystal_I2C lcd(0x27,20,4); 
#define TRIGGER_PIN 0
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY,"","");
//AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#include "Packet.h"
byte  flgwifi = 0;
////////////////////////////////////
byte  TrasmettiAda = 1;   // if 0 it doesn't connect to WiFi and Adafruit
/////////////////////////////////////
float TimeOld = 0;
float TimePassed = 0;
uint16_t MM[20];
/////////////////////////////////////////////////////
void setup() {
  delay(5000);
  
  //  Begin LCD
 // Wire.begin(OLED_SDA,OLED_SCL);
  Wire.begin(21,22);  //  Schede nuove  TTGO LoRa32 SX1276 con OLED

  delay(1000);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RX_LoRa_Generic");
 
  //  Begin Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  delay(500);
  Serial.println("RX_Generic_Autoconnect_WiFi_button_LCD");
  pinMode(LED,OUTPUT); // Green Led
  pinMode(VBAT,INPUT); // Input for Battery Voltage
   
  // Begins LoRa Module
  lcd.setCursor(0,1);  
  lcd.print("Begin LoRa");
  lcd.setCursor(0,2);  
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  if (!LoRa.begin(LORA_BAND)){
     Serial.println("LoRa failed");
     lcd.print("LoRa failed");
     while (1);
  }  
  Serial.println("LoRa OK");
   lcd.print("LoRa OK!");
// LoRa.setSpreadingFactor(8);           // ranges from 6-12,default 7 see API docs
//  LoRa.setTxPower(int level, int outputPin)  // max level 20
//  LoRa.setTxPower(int level, int outputPin = PA_OUTPUT_PA_BOOST_PIN);  // ?
  
  delay(3000);
  
//  Begin WiFi connection
       WiFi.mode(WIFI_STA);
      Serial.print("Connecting to WiFi ");
      Serial.println(WIFI_STA);
      Serial.println();
      Serial.print("Wait for WiFi... ");Serial.println(WIFI_SSID);
      lcd.clear();  
      lcd.print("Connecting to WiFi");
      lcd.setCursor(0,1); 
      lcd.setCursor(0,2); 
//      lcd.print(WIFI_SSID);
      delay(3000);
      
  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
      WiFiManager wm;
  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
 //       String ssdi = wm.getDefaultAPName();
 //      Serial.println(ssdi);       

    pinMode(TRIGGER_PIN, INPUT_PULLUP); 
    Serial.println("Push button for input within 5 sec");
    lcd.clear();
    lcd.print("Push button to enter");
    lcd.setCursor(0,1); 
    lcd.print("credential within 5s");
    byte demand = 0;    
     demand =    PushButt(5000);  // =1 if you push button within 5 s
    Serial.print("demand ");Serial.println(demand);
    lcd.setCursor(0,2); 
    if(demand){
      wm.resetSettings();
      lcd.print("Connecting to ESP32");
      Serial.println("Connecting to ESP32");
    }else{
     lcd.print("Connecting old SSID");
    Serial.println("Connecting to old SSID");
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
    if(!res) {
       Serial.println("Failed to connect");
       lcd.print("Failed to connect");       
//       ESP.restart();
       flgwifi = 0;
       TrasmettiAda = 0;       
    }else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
        lcd.print("Connected!!");     
        flgwifi = 1;    
    }
    Serial.println(TrasmettiAda,DEC);
    delay(3000);
    
// Connecting to Adafruit
 if(TrasmettiAda){  
  lcd.clear();
  lcd.print("Connecting Adafruit");
  lcd.setCursor(0,1);
  Serial.printf("Connecting to Adafruit IO with User: %s Key: %s.\n", IO_USERNAME, IO_KEY);
  io.connect();    
  TimeOld = millis();
  while ((io.status() < AIO_CONNECTED)){
      Serial.println(io.status());
      TimePassed = millis() - TimeOld;
      if(TimePassed > 20000){
         TrasmettiAda = 0; 
         break;
      }
      delay(500);
    }
    if(TrasmettiAda){
       Serial.println("Connected to Adafruit IO.");
       lcd.print("Connected!!");
    }else{
      Serial.println("Failed to connect to Adafruit");
      lcd.print("No Adafruit Server");
    }      
     
//  print on display
         Serial.println("IP address: ");
         Serial.println(WiFi.localIP());         
         lcd.setCursor(0,2);      
         lcd.print(WiFi.localIP());   
         Serial.print(" io.status ");
 }
// Initialize MM for 12140
 for(int g = 0; g < 20; g++){
      MM[g] = 0;
 }  
}
//////////////////////////////////////////////// 
void loop() {

// check if connection is alive, otherwise it restarts
  if(TrasmettiAda){
   int pippo =   io.run();
//   Serial.println(pippo);
   if(pippo != 21){
    ESP.restart();
    delay(1000);
   }
 }    

  Roger = Receive();  
  if(Roger){
    Action();
    Roger = 0;
  }
 // delay(1);   // Pay attention!  Too long a delay can cause the card to become deaf to some messages 
}
