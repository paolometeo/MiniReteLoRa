void Print49004(){
  /*

*/
  arrived_49004++;
  Serial.print("arrived_49004 ");Serial.println(arrived_49004);
  Serial.print(" npulse_4 "); 
  Serial.print(minni.Data49004.npulse_4);
  Serial.print("  speriod_4 ");
  Serial.print(minni.Data49004.speriod_4);
  Serial.print("  degree_4 ");
  Serial.print(minni.Data49004.degree_4);
  Serial.print("  degreeMA_4 ");
  Serial.print(minni.Data49004.degreeMA_4);
  Serial.print("  degreeSD_4 ");
  Serial.print(minni.Data49004.degreeSD_4);
  Serial.println();
  lcd.setCursor(0,2);
  lcd.print(minni.Data49004.npulse_4);lcd.print(" ");
  lcd.print(minni.Data49004.speriod_4);lcd.print(" ");
  lcd.print(minni.Data49004.degree_4,1);lcd.print(" ");
  lcd.print(minni.Data49004.degreeSD_4);lcd.print(" ");

 if(!nowifi){
//  Transmission to the Internet Server
    TimePassed_Ada = millis() - TimeOld_Ada;    
    if(TrasmettiAda && ( TimePassed_Ada > Period_Ada)){
           nPulse4   ->   save(minni.Data49004.npulse_4);
           sPeriod4  ->   save(minni.Data49004.speriod_4);
           degree4  ->    save(minni.Data49004.degree_4);
           degreeMA4  ->  save(minni.Data49004.degreeMA_4);
           degreeSD4  ->  save(minni.Data49004.degreeSD_4);
           NPACKET4 ->    save(npacket);
           BATTERY4 ->    save(vBatTX);
           RSSI4    ->    save(nRSSI);
           arrived4 ->    save(arrived_49004);
           nrestart ->    save(nRestart);

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
