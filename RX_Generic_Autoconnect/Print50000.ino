//  Temp, Humid. and light AM2301B
void Print50000(){
         Serial.print(" Tair "); 
         Serial.print(minni.Data50000.Tair);
         Serial.print("  Humi ");
         Serial.print(minni.Data50000.Umid);
         Serial.print("  Light ");
         Serial.print(minni.Data50000.Light);
         Serial.println();
/*         
      display.drawString(0,22,"Tair: " + String(minni.Data50000.Tair));
      display.drawString(0,33,"Umid: " + String(minni.Data50000.Umid));
      display.clear();
*/
//  Transmission to the Internet Server
      if(TrasmettiAda){
           Tair->    save(minni.Data50000.Tair);
           Umid->    save(minni.Data50000.Umid);
           Light->    save(minni.Data50000.Light);
           Serial.println("Inviato a Adafruit");           
      }
}
