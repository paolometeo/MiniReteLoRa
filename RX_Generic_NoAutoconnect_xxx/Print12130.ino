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
  display.drawString(0,22,"Conc10: " + String(minni.Data12130.Conc10));
  display.drawString(0,33,"Conc25: " + String(minni.Data12130.Conc25));
  display.display();

//  Transmission to the Internet Server
      if(TrasmettiAda){
           Conc25   ->   save(minni.Data12130.Conc25);
           Conc10 ->     save(minni.Data12130.Conc10);
           UMID ->       save(minni.Data12130.UMID);
           TEMP ->       save(minni.Data12130.TEMP);
           Serial.println("Inviato a Adafruit");     
      }
}