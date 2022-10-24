byte Receive(){
    byte Received = 0;
    int packetSize = LoRa.parsePacket();
    if(packetSize == 0){
       Received = 0;
       return Received;
    }else{
       Serial.print(" packetSize ");Serial.println(packetSize);
       len = packetSize - 4;
       Serial.print(" payloadSize ");Serial.println(len);
    // read packet
       int j=0;
       int jj = 0;
       Serial.println(" Byte received ");
       while (LoRa.available()) {
         byte pippo = LoRa.read();
         Serial.print(pippo, HEX);Serial.print(" ");
         j++;
         if(j >=5){
          jj = j-5;
          buf[jj]=pippo;
         }
       }
       Serial.println();
       Serial.println(" Message ");
       for(int jj = 0; jj < 12; jj++){
           Serial.print(buf[jj], HEX);Serial.print(" ");
       }
       Serial.println();
       
// print RSSI of packet
       Serial.print(" with RSSI: ");
       byte ciccio = LoRa.packetRssi();
       nRSSI = abs(ciccio - 256);
       Serial.println(nRSSI);
       
// Blinking and decode heading
      Blinking();    
      ID_TX =   buf[1]*256+buf[0];
      Length =  buf[3]*256+buf[2];
      vBatTX =  buf[5]*256+buf[4];
      npacket = buf[7]*256+buf[6];      
      if(len != Length){
         Serial.println(" Length not permitted ");
        Received = 0;
        return Received;
      }

//  decode data
      for (i = 8; i < Length; i++){
        minni.bufVar[i-8] = buf[i];
      } 
         
//   Clear the receiving buffer
      for(i = 0; i < MXbuf; i++){
            buf[i] = 0;
      } 
      Serial.print("  bufVar content: ");
      for (i = 8; i < Length; i++){
           Serial.print(minni.bufVar[i-8],HEX); Serial.print(" ");
      }
      Serial.println(); 
      Serial.print("ID_TX ");Serial.print(ID_TX);
      Serial.print(" Length ");Serial.print(Length);
      Serial.print(" vBatTX ");Serial.print(vBatTX);
      Serial.print(" npacket ");Serial.print(npacket); 
      Serial.println();
      
      if(npacket > 9999){
            npacket = npacket%10000;
      }
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("ID: "); display.print(ID_TX);
      display.setCursor(64,0);
      display.print("np: "); display.print(npacket);
      display.setCursor(0,11);
      display.print("nRSSI: "); display.print(nRSSI);
      display.setCursor(64,11);
      display.print("Bat: "); display.print(vBatTX);
      display.display();
      Received = 1;
      return Received;
  }
}
