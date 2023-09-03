void TransmitRIP(){

//  read battery voltage
    uint16_t vBatTX = Battery(); 
    ID_TX = 12129;
  // Build the buf array
  buf[0]=lowByte(ID_TX);
  buf[1]=highByte(ID_TX);
  buf[2]=lowByte(LengthRIP);
  buf[3]=highByte(LengthRIP);
  buf[4]=lowByte(vBatTX);
  buf[5]=highByte(vBatTX);
  buf[6]=lowByte(npacketRIP);
  buf[7]=highByte(npacketRIP);

//  fill the buf array with the variable array
for(uint16_t i = 8; i < LengthRIP; i++){
  buf[i] = minni.bufVar[i-8];
}
  
// Transmission
  if(ECHO){
     Serial.println("Sending...");
  }
  rf95.send((uint8_t *)buf, LengthRIP);
  altDelay(10);
  if(ECHO){
     Serial.println("Waiting for packet to complete..."); 
  }
  rf95.waitPacketSent();
  if(ECHO){
    Serial.println(" packet complete ");
  }
  if(ECHO){
    Serial.println(" Message HEX");
    for(uint16_t g = 0; g < LengthRIP; g++){
       Serial.print(buf[g],HEX);Serial.print(" ");
    }
    Serial.println();
    Serial.println(" Message Dec");
    Serial.print(ID_TX);Serial.print(" ");Serial.print(LengthRIP);Serial.print(" ");
    Serial.print(vBatTX);Serial.print(" ");Serial.print(npacketRIP);Serial.print(" ");
    Serial.println(minni.Data12129.stato);
  }
  //  increase the packet number
  npacketRIP++;
  if(npacketRIP > 60000){
    npacketRIP = 0;
  }

// Blinking
  Blinking();

// reset buf
  for(uint16_t g = 0; g < MXbuf; g++){
       buf[g] = 0;
  }
  for(uint16_t g = 0; g < MXVAR; g++){
       minni.bufVar[g] = 0;
  }
}
