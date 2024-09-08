void Print49003(){
  /*

*/
  arrived_49003++;
  Serial.print(" npulse_3 "); 
  Serial.print(minni.Data49003.npulse_3);
  Serial.print("  speriod_3 ");
  Serial.print(minni.Data49003.speriod_3);
  Serial.print("  degree_3 ");
  Serial.print(minni.Data49003.degree_3);
  Serial.print("  degreeMA_3 ");
  Serial.print(minni.Data49003.degreeMA_3);
  Serial.print("  degreeSD_3 ");
  Serial.print(minni.Data49003.degreeSD_3);
  Serial.println();
  lcd.setCursor(0,2);
  lcd.print(minni.Data49003.npulse_3);lcd.print(" ");
  lcd.print(minni.Data49003.speriod_3);lcd.print(" ");
  lcd.print(minni.Data49003.degree_3,1);lcd.print(" ");
  lcd.print(minni.Data49003.degreeSD_3);lcd.print(" ");

 if(!nowifi){
//  Transmission to the Internet Server
    TimePassed_Ada = millis() - TimeOld_Ada;    
    if(TrasmettiAda && ( TimePassed_Ada > Period_Ada)){
           nPulse3   ->   save(minni.Data49003.npulse_3);
           sPeriod3  ->   save(minni.Data49003.speriod_3);
           degree3  ->    save(minni.Data49003.degree_3);
           degreeMA3  ->  save(minni.Data49003.degreeMA_3);
           degreeSD3  ->  save(minni.Data49003.degreeSD_3);
           NPACKET3 ->    save(npacket);
           BATTERY3 ->    save(vBatTX);
           RSSI3    ->    save(nRSSI);
           arrived3 ->    save(arrived_49003);

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
