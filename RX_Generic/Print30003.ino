// DHT 22
void Print30003(){
         Serial.print(" Temp "); 
         Serial.print(minni.Data30003.Temp);
         Serial.print("  Humi ");
         Serial.print(minni.Data30003.Humi);
         Serial.println();
      display.drawString(0,22,"npulse: " + String(minni.Data30003.Temp));
      display.drawString(0,33,"sPeriod: " + String(minni.Data30003.Humi));
      display.display();

//  Transmission to the Internet Server
      if(TrasmettiAda){
           Temp ->    save(minni.Data30003.Temp);
           Humi ->    save(minni.Data30003.Humi);
      }
}
