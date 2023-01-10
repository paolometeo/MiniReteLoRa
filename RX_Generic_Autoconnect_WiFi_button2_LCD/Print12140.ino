void Print12140(){
/*
uint16_t       npulse;       //  number of pulses from Rain Gauge
uint16_t       Per;          //  Period of time (s) in which pulses are counted
uint16_t       Irain;        //  rain intensity in 0.1 mm/min
uint8_t       WetnessA;         //  value from wetness sensor A
uint8_t       WetnessB;         //  value from wetness sensor B
*/
  
  Serial.print(" npulse "); 
  Serial.print(minni.Data12140.npulse);
  Serial.print("  Per ");
  Serial.print(minni.Data12140.Per);
  Serial.print("  Irain ");
  Serial.print(minni.Data12140.Irain);
  Serial.print("  WetA ");
  Serial.print(minni.Data12140.WetnessA);
  Serial.print("  WetB ");
  Serial.print(minni.Data12140.WetnessB);
  Serial.println();
  lcd.setCursor(0,2);
  lcd.print(minni.Data12140.npulse);lcd.print(" ");lcd.print(minni.Data12140.Per);lcd.print(" ");
  lcd.print(minni.Data12140.Irain);lcd.print(" ");  
  lcd.print(minni.Data12140.WetnessA);lcd.print(" ");lcd.print(minni.Data12140.WetnessB);

//  compute RainH  0.1 mm/h
// shift by one M
   for(int g = 1; g < 20; g++){
      MM[g-1] = MM[g];
   }
   MM[19] = minni.Data12140.Irain;
//  accumulate the 20 values of 3 minutes rain
   int sum = 0;
   for(int g = 0; g < 20; g++){
      sum = sum + MM[g];
   }
   lcd.print(" ");lcd.print(sum);
//  Transmission to the Internet Server
      if(TrasmettiAda){
           n   ->       save(minni.Data12140.npulse);
           Per ->       save(minni.Data12140.Per);
           Irain ->     save(minni.Data12140.Irain);
           WetnessA ->  save(minni.Data12140.WetnessA);
           WetnessB ->  save(minni.Data12140.WetnessB);
           npack ->     save(npacket);
           Bat     ->   save(vBatTX);
           RainH  ->    save(sum);         
           Serial.println("Inviato a Adafruit");           
           lcd.setCursor(0,3);
           lcd.print("Sent to the Server");
      }
}
