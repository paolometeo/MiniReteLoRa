void Print12127(){
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

    Serial.print(F("mA da ina1 a batteria   "));Serial.println(minni.Data12127.curr1,1);
    Serial.print(F("mA da FV a regolatore   "));Serial.println(minni.Data12127.curr2,1);
    Serial.print(F("tensione della batteria "));Serial.println(minni.Data12127.Volt1,1);
    Serial.print(F("tensione di FV          "));Serial.println(minni.Data12127.Volt2,1);
    Serial.println();
  
//  Transmission to the Internet Server
      if(TrasmettiAda){
           curr1   ->   save(minni.Data12127.curr1);
           curr2 ->     save(minni.Data12127.curr2);
           Volt1 ->     save(minni.Data12127.Volt1);
           Volt2 ->     save(minni.Data12127.Volt2);  
           Serial.println("Inviato a Adafruit");
      }

}