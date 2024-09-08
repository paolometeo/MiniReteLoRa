byte Receive(){
    byte Received = 0;
    int packetSize = LoRa.parsePacket();
    if(packetSize == 0){
       Received = 0;
       return Received;
    }else{
       Serial.println();     
       Serial.println("                                                 New packet");
       Serial.print(" packetSize ");Serial.println(packetSize);
        len = packetSize;
       Serial.print(" payloadSize ");Serial.println(len);
       lcd.clear();
       
           // read packet
       int jj = 0;
       Serial.println(" Byte received ");
       while (LoRa.available()) {
         byte pippo = LoRa.read();
         Serial.print(pippo, HEX);Serial.print(" ");
         buf[jj]=pippo;
         jj++;
         if(jj >= MXbuf){
          Received = 0;
          return Received;
         }
       }
       Serial.println();
       if(buf[0] == 0xFF && buf[1] == 0xFF && buf[2] == 0x00 && buf[3] == 0x00){
         for(int j = 0; j < len-4; j++){
           buf[j] = buf[j+4];
         }
         len = len - 4;
         Serial.print(" Corrected len ");Serial.println(len);
       }
       Serial.println();
       Serial.println(" Message heading HEX");
       for(int jj = 0; jj < 8; jj++){
           Serial.print(buf[jj], HEX);Serial.print(" ");
       }
       Serial.println();
       
// print RSSI of packet
       Serial.print("with RSSI: ");
       byte ciccio = LoRa.packetRssi();
       nRSSI = abs(ciccio - 256);
       Serial.println(nRSSI);
       lcd.print("Received with R");lcd.print(nRSSI);
/*
       lcd.setCursor(0,1);
        for(int jj = 0; jj < 8; jj++){
            lcd.print(buf[jj], HEX);lcd.print(" ");
        }
*/
// Blinking and decode heading
      Blinking();    
      ID_TX =   buf[1]*256+buf[0];
      Length =  buf[3]*256+buf[2];
      vBatTX =  buf[5]*256+buf[4];
      npacket = buf[7]*256+buf[6];      
      if(len != Length){
         Serial.println(" Length not permitted ");
         lcd.setCursor(0,2);
         lcd.print("Length not permitted");
         Received = 0;
         return Received;
      }

//  decode data
      for (int i = 8; i < Length; i++){
        minni.bufVar[i-8] = buf[i];
      } 
         
//   Clear the receiving buffer
      for(int i = 0; i < MXbuf; i++){
            buf[i] = 0;
      } 
      Serial.print("bufVar content: ");
      for (int i = 8; i < Length; i++){
           Serial.print(minni.bufVar[i-8],HEX); Serial.print(" ");
      }
      Serial.println(); 
      Serial.println("Message heading DEC ");
      Serial.print("ID_TX ");Serial.print(ID_TX);
      Serial.print(" Length ");Serial.print(Length);
      Serial.print(" vBatTX ");Serial.print(vBatTX);
      Serial.print(" npacket ");Serial.print(npacket); 
      Serial.println();
      lcd.setCursor(0,1);
      lcd.print(ID_TX);lcd.print(" ");
      lcd.print(Length);lcd.print(" ");
      lcd.print(vBatTX);lcd.print(" ");
      lcd.print(npacket);
      if(npacket > 9999){
            npacket = npacket%10000;
      }
      Received = 1;
      return Received;
  }
}
