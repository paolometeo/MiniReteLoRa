void Print49010(){
 /*

*/
  arrived_49010++;
  Serial.print(" StatoRip "); 
  Serial.print(minni.Data49010.stato);
  Serial.print(" ");
  Serial.println();
  lcd.setCursor(0,2);
  if(minni.Data49010.stato == 1){
    lcd.print("StatoRip: OK");
    Serial.println("StatoRip: OK");
    lcd.setCursor(0,3);
  }
  if(minni.Data49010.stato == 2){
    lcd.print("StatoRip: noMessage");
    lcd.setCursor(0,3);
    lcd.print("rec. from setup");
    Serial.println("StatoRip: noMessage rec. from setup ");
  }
    if(minni.Data49010.stato == 3){
    lcd.print("StatoRip: noMessage");
    lcd.setCursor(0,3);
    lcd.print("rec. from loop");
    Serial.println("StatoRip: noMessage rec. from loop ");
  }

  if(minni.Data49010.stato == 0){
    lcd.print("StatoRip: error");
    Serial.println("StatoRip: error");
  }

//  Transmission to the Internet Server
    TimePassed_Ada = millis() - TimeOld_Ada;    
    if(TrasmettiAda && ( TimePassed_Ada > Period_Ada)){
 
          StatoRip   ->   save(minni.Data49010.stato);
          RSSIrip    ->   save(nRSSI);
          BATTERYrip ->   save(vBatTX);
          NPACKETrip ->   save(npacket);
          arrived10  ->   save(arrived_49010);

           Serial.println("Inviato a Adafruit");   
           lcd.setCursor(0,3);
           lcd.print("Sent to the Server");
           TimeOld_Ada = millis();
    }
}
