void RadioInit() {
  /*
TX Power
Change the TX power of the radio.
LoRa.setTxPower(txPower);
LoRa.setTxPower(txPower, outputPin); 
TX power in dB, defaults to 17;  outputPin - (optional) PA output pin, 
supported values are PA_OUTPUT_RFO_PIN and PA_OUTPUT_PA_BOOST_PIN, defaults to PA_OUTPUT_PA_BOOST_PIN.
Supported values are 2 to 20 for PA_OUTPUT_PA_BOOST_PIN, and 0 to 14 for PA_OUTPUT_RFO_PIN.
Most modules have the PA output pin connected to PA BOOST,
  */

LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT); // set CS, reset, IRQ pin

  pinMode(LEDpin, OUTPUT);
  if (LEDpin == 17) {
    digitalWrite(LEDpin, HIGH);
  } else {
    digitalWrite(LEDpin, LOW);
  }
 
  if (!LoRa.begin(RF95_FREQ)) {     
       if(ECHO)Serial.println("LoRa init failed. Check your connections.");
       while (true);                       // if failed, do nothing
  }
  /*
  Signal Bandwidth
Change the signal bandwidth of the radio.
LoRa.setSignalBandwidth(signalBandwidth);
signalBandwidth - signal bandwidth in Hz, defaults to 125E3.
Supported values are 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3, 41.7E3, 62.5E3, 125E3, 250E3, and 500E3 (not in Europe).
  */
//  LoRa.setSignalBandwidth(250E3);
  LoRa.setSpreadingFactor(SF);           // ranges from 6-12,default 7 see API docs
  LoRa.setTxPower(RF95_POW);
  if (ECHO) {
      Serial.print(F("Set Freq to: ")); Serial.println(RF95_FREQ);
      Serial.print(F("Set Power to: ")); Serial.println(RF95_POW);
      Serial.println("LoRa init succeeded.");
  }
  npacket = 0;
}
