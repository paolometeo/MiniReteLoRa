void Print49001(){
  /*
uint16_t arrived_49001 = 0;
uint16_t arrived_49002 = 0;
uint16_t arrived_49003 = 0;
uint16_t arrived_49004 = 0;
uint16_t arrived_49010 = 0;

*/
  arrived_49001++;
  Serial.print(" npulse_1 "); 
  Serial.print(minni.Data49001.npulse_1);
  Serial.print("  speriod_1 ");
  Serial.print(minni.Data49001.speriod_1);
  Serial.print("  degree_1 ");
  Serial.print(minni.Data49001.degree_1);
  Serial.print("  degreeMA_1 ");
  Serial.print(minni.Data49001.degreeMA_1);
  Serial.print("  degreeSD_1 ");
  Serial.print(minni.Data49001.degreeSD_1);
  Serial.println();
  lcd.setCursor(0,2);
  lcd.print(minni.Data49001.npulse_1);lcd.print(" ");
  lcd.print(minni.Data49001.speriod_1);lcd.print(" ");
  lcd.print(minni.Data49001.degree_1,1);lcd.print(" ");
  lcd.print(minni.Data49001.degreeSD_1);lcd.print(" ");

 if(!nowifi){
//  Transmission to the Internet Server
    TimePassed_Ada = millis() - TimeOld_Ada;    
    if(TrasmettiAda && ( TimePassed_Ada > Period_Ada)){
           nPulse1   ->   save(minni.Data49001.npulse_1);
           sPeriod1  ->   save(minni.Data49001.speriod_1);
           degree1  ->    save(minni.Data49001.degree_1);
           degreeMA1  ->  save(minni.Data49001.degreeMA_1);
           degreeSD1  ->  save(minni.Data49001.degreeSD_1);
           NPACKET1 ->    save(npacket);
           BATTERY1 ->    save(vBatTX);
           RSSI1    ->    save(nRSSI);
           arrived1 ->    save(arrived_49001);

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
