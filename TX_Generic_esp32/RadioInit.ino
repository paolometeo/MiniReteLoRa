void RadioInit(){
  /*
   * radio init
 Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol,CRC on
 The default transmitter power is 13dBm, using PA_BOOST.
 If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
 you can set transmitter powers from 5 to 23 dBm:

 Set frequency. Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM 
 rf95.printRegisters();  //Print all the RFM95 register values
 rf95.setModemConfig(RH_RF95::Bw31_25Cr48Sf512);
 rf95.setModemConfig(rf95.Bw31_25Cr48Sf512);

 Bw125Cr45Sf128   Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on. 
 Default medium range.
 Bw500Cr45Sf128  Bw = 500 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on. 
 Fast+short range.
 Bw31_25Cr48Sf512  Bw = 31.25 kHz, Cr = 4/8, Sf = 512chips/symbol, CRC on. 
 Slow+long range.
 Bw125Cr48Sf4096   Bw = 125 kHz, Cr = 4/8, Sf = 4096chips/symbol, CRC on. 
 Slow+long range.
  */
if(ECHO) Serial.println(" Inizializzo SPI"); //SPI LoRa pins

//  SPI.begin(SCK, MISO, MOSI, RFM95_CS);  

  //setup LoRa transceiver module
  pinMode(RFM95_RST, OUTPUT);      // equivale al tasto del reset
  digitalWrite(RFM95_RST, HIGH);   //  pullup sul tasto reset
  pinMode(LEDpin, OUTPUT);
  if(LEDpin == 17){
    digitalWrite(LEDpin,HIGH);
  }else{
    digitalWrite(LEDpin,LOW);
  }

    // manual reset of the radio
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  
  while (!rf95.init()) {
    if (ECHO) {
      Serial.println("LoRa radio init failed");
    }
  }
  if (ECHO) {
    Serial.println("LoRa radio init OK!");
  }
}
