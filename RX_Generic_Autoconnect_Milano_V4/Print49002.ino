void Print49002(){
  /*

*/
  arrived_49002++;
  Serial.print(" npulse_2 "); 
  Serial.print(minni.Data49002.npulse_2);
  Serial.print("  speriod_2 ");
  Serial.print(minni.Data49002.speriod_2);
  Serial.print("  degree_2 ");
  Serial.print(minni.Data49002.degree_2);
  Serial.print("  degreeMA_2 ");
  Serial.print(minni.Data49002.degreeMA_2);
  Serial.print("  degreeSD_2 ");
  Serial.print(minni.Data49002.degreeSD_2);
  Serial.println();
  lcd.setCursor(0,2);
  lcd.print(minni.Data49002.npulse_2);lcd.print(" ");
  lcd.print(minni.Data49002.speriod_2);lcd.print(" ");
  lcd.print(minni.Data49002.degree_2,1);lcd.print(" ");
  lcd.print(minni.Data49002.degreeSD_2);lcd.print(" ");

 if(!nowifi){
//  Transmission to the Internet Server
    TimePassed_Ada = millis() - TimeOld_Ada;    
    if(TrasmettiAda && ( TimePassed_Ada > Period_Ada)){
           nPulse2   ->   save(minni.Data49002.npulse_2);
           sPeriod2  ->   save(minni.Data49002.speriod_2);
           degree2  ->    save(minni.Data49002.degree_2);
           degreeMA2  ->  save(minni.Data49002.degreeMA_2);
           degreeSD2  ->  save(minni.Data49002.degreeSD_2);
           NPACKET2 ->    save(npacket);
           BATTERY2 ->    save(vBatTX);
           RSSI2    ->    save(nRSSI);
           arrived2 ->    save(arrived_49002);

           Serial.println("Inviato a Adafruit");   
           lcd.setCursor(0,3);
           lcd.print("Sent to the Server");
           TimeOld_Ada = millis();
    }
    }else{
      lcd.setCursor(0,3);
      lcd.print("You choose no WiFi");
      Serial.println("You choose no WiFi");
    }
       ID_TX = 0;
}
