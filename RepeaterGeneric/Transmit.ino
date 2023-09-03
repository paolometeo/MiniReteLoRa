void Transmit(){
  
  // Build the buf array
  buf[0]=lowByte(ID_TX);
  buf[1]=highByte(ID_TX);
  buf[2]=lowByte(Length);
  buf[3]=highByte(Length);
  buf[4]=lowByte(vBatTX);
  buf[5]=highByte(vBatTX);
  buf[6]=lowByte(npacket);
  buf[7]=highByte(npacket);

//  fill the buf array with the variable array
for(uint16_t i = 8; i < Length; i++){
  buf[i] = minni.bufVar[i-8];
}
  
// Transmission
  if(ECHO){
     Serial.println("Sending...");
  }
  rf95.send((uint8_t *)buf, Length);
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
    for(uint16_t g = 0; g < Length; g++){
       Serial.print(buf[g],HEX);Serial.print(" ");
    }
    Serial.println();
    Serial.println(" Message Dec");
    Serial.print(ID_TX);Serial.print(" ");Serial.print(Length);Serial.print(" ");
    Serial.print(vBatTX);Serial.print(" ");Serial.print(npacket);Serial.println(" ");
    Serial.print(F("tensione della batteria "));Serial.println(minni.Data12127.Volt1,1);
    Serial.print(F("tensione di FV          "));Serial.println(minni.Data12127.Volt2,1);
    Serial.print(F("mA da ina1 a batteria   "));Serial.println(minni.Data12127.curr1,1);
    Serial.print(F("mA da FV a regolatore   "));Serial.println(minni.Data12127.curr2,1);
    Serial.print(F("T1   "));Serial.println(minni.Data12127.T1,1);
    Serial.print(F("T2   "));Serial.println(minni.Data12127.T2,1);
    Serial.print(F("T3   "));Serial.println(minni.Data12127.T3,1);
    Serial.println();
    Serial.println();
  }
  //  increase the packet number
  npacket++;
  if(npacket > 60000){
    npacket = 0;
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
