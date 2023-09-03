void Print12127(){
  float power1 = 0;
  float power2 = 0;
  float rapp = 0  ;  
/*
  //  Solar Test Panel
typedef struct packet12127{
float  curr1;   //  corrente in mA da ina1  batteria
float  curr2;   //  corrente in mA da ina2  FV
float  Volt1;   //  tensione della batteria
float  Volt2;   //  tensione del FV
};
AdafruitIO_Feed *curr1 = io.feed("curr1");
AdafruitIO_Feed *curr2 = io.feed("curr2");
AdafruitIO_Feed *Volt1 = io.feed("Volt1");
AdafruitIO_Feed *Volt2 = io.feed("Volt2");
*/

    Serial.print(F("mA da ina1 a batteria (curr1)   "));Serial.println(minni.Data12127.curr1,1);
    Serial.print(F("mA da FV a regolatore (curr2)  "));Serial.println(minni.Data12127.curr2,1);
    Serial.print(F("tensione della batteria (Volt1)"));Serial.println(minni.Data12127.Volt1,1);
    Serial.print(F("tensione di FV    (Volt2)      "));Serial.println(minni.Data12127.Volt2,1);
    Serial.print(F("RMS mA da ina1 a batteria (curr1)   "));Serial.println(minni.Data12127.curr1q,4);
    Serial.print(F("RMS mA da FV a regolatore (curr2)  "));Serial.println(minni.Data12127.curr2q,4);
    Serial.print(F("RMS tensione della batteria (Volt1)"));Serial.println(minni.Data12127.Volt1q,4);
    Serial.print(F("RMS tensione di FV    (Volt2)      "));Serial.println(minni.Data12127.Volt2q,4);
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
           curr1q   ->   save(minni.Data12127.curr1q);
           curr2q ->     save(minni.Data12127.curr2q);
           Volt1q ->     save(minni.Data12127.Volt1q);
           Volt2q ->     save(minni.Data12127.Volt2q);  
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
 Power1   ->   save(power1);
 Power2   ->   save(power2);
 //Rapp   ->   save(rapp);
}