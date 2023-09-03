void Print12130(){
  /*
//  Dust sensor (Perlongo)
typedef struct packet12130{
float      Conc25;   
float      Conc10;
float      UMID;    
float      TEMP;    
};
AdafruitIO_Feed *Conc25 = io.feed("Conc25");
AdafruitIO_Feed *Conc10 = io.feed("Conc10");
AdafruitIO_Feed *UMID = io.feed("UMID");
AdafruitIO_Feed *TEMP = io.feed("TEMP");

*/
  Serial.print(" Conc25 "); 
  Serial.print(minni.Data12130.Conc25);
  Serial.print("  Conc10 ");
  Serial.print(minni.Data12130.Conc10);
  Serial.print("  UMID ");
  Serial.print(minni.Data12130.UMID);
  Serial.print("  TEMP ");
  Serial.print(minni.Data12130.TEMP);
  Serial.println();
  lcd.setCursor(0,2);
  lcd.print(minni.Data12130.Conc25,1);lcd.print(" ");lcd.print(minni.Data12130.Conc10,1);lcd.print(" ");
  lcd.print(minni.Data12130.TEMP,1);lcd.print(" ");  
  lcd.print(minni.Data12130.UMID,0);
//  Transmission to the Internet Server
      if(TrasmettiAda){
           Conc25   ->   save(minni.Data12130.Conc25);
           Conc10 ->     save(minni.Data12130.Conc10);
           UMID ->       save(minni.Data12130.UMID);
           TEMP ->       save(minni.Data12130.TEMP);
           Serial.println("Inviato a Adafruit");   
           lcd.setCursor(0,3);
           lcd.print("Sent to the Server");
      }
}