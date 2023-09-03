void Print12127(){
  float power1 = 0;
  float power2 = 0;
  float rapp = 0  ;  

    Serial.print(F("mA da ina1 a batteria (curr1)  "));Serial.println(minni.Data12127.curr1,1);
    Serial.print(F("mA da FV a regolatore (curr2)  "));Serial.println(minni.Data12127.curr2,1);
    Serial.print(F("tensione della batteria (Volt1)"));Serial.println(minni.Data12127.Volt1,1);
    Serial.print(F("tensione di FV          (Volt2)"));Serial.println(minni.Data12127.Volt2,1);
    Serial.print(F("Temp1                          "));Serial.println(minni.Data12127.T1,1);
    Serial.print(F("Temp2                          "));Serial.println(minni.Data12127.T2,1);
    Serial.print(F("Temp3                         "));Serial.println(minni.Data12127.T3,1);
  
    Serial.println();
    lcd.setCursor(0,2);
    lcd.print("I-B ");lcd.print(minni.Data12127.curr1,1);lcd.print(" I-FV ");lcd.print(minni.Data12127.curr2,1); 
    lcd.setCursor(0,3);
    lcd.print("V-B ");lcd.print(minni.Data12127.Volt1,1);lcd.print(" V-FV ");lcd.print(minni.Data12127.Volt2,1);
//  Transmission to the Internet Server
      if(TrasmettiAda){
           curr1   ->   save(minni.Data12127.curr1);
           curr2 ->     save(minni.Data12127.curr2);
           Volt1 ->     save(minni.Data12127.Volt1);
           Volt2 ->     save(minni.Data12127.Volt2);  
           TT1 ->     save(minni.Data12127.T1);  
           TT2 ->     save(minni.Data12127.T2);  
           TT3 ->     save(minni.Data12127.T3);  
           Serial.println("Inviato a Adafruit");
      }
// Calcolo potenze
 power1 = minni.Data12127.curr1  *minni.Data12127.Volt1;
 power2 = minni.Data12127.curr2  *minni.Data12127.Volt2;
if(power2 > 0){
   rapp = 100*power1/power2;
}else{
 rapp =   0;
 }
 Serial.print(" Rapporto tra potenze ");Serial.println(rapp,1);
 if(TrasmettiAda){
   Power1   ->   save(power1);
   Power2   ->   save(power2);
 }
}