void Print41001(){
/*
typedef struct packet41001{
uint16_t       npulse2024_1;   
uint16_t       npulse2024_2;   
uint16_t       speriod2024;   
float          BMEtemp;
float          BMEhum;
float          BMEpres;
};
*/
  Serial.print(minni.Data41001.npulse2024_1);
  Serial.print(" ");
  Serial.print(minni.Data41001.npulse2024_2);
  Serial.print(" ");
  Serial.print(minni.Data41001.speriod2024);
  Serial.print(" ");
  Serial.print(minni.Data41001.BMEtemp);
  Serial.print(" ");
  Serial.print(minni.Data41001.BMEhum);
  Serial.print(" ");
  Serial.print(minni.Data41001.BMEpres);
  Serial.print(" ");
  Serial.println();
  lcd.setCursor(0,2);
  lcd.print(minni.Data41001.npulse2024_1);lcd.print(" ");
  lcd.print(minni.Data41001.npulse2024_2);lcd.print(" impulsi");

//  Transmission to the Internet Server
    TimePassed_Ada = millis() - TimeOld_Ada;    
    if(TrasmettiAda && ( TimePassed_Ada > Period_Ada)){
 
          NPULSE2024_1   ->   save(minni.Data41001.npulse2024_1);
          NPULSE2024_2   ->   save(minni.Data41001.npulse2024_2);
          SPERIOD2024   ->    save(minni.Data41001.speriod2024);
          BMETEMP   ->        save(minni.Data41001.BMEtemp);
          BMEHUM   ->         save(minni.Data41001.BMEhum);
          BMEPRES   ->        save(minni.Data41001.BMEpres);

           Serial.println("Inviato a Adafruit");   
           lcd.setCursor(0,3);
           lcd.print("Sent to the Server");
           TimeOld_Ada = millis();
}
}
