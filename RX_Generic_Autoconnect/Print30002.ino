//  Sound Sensor
void Print30002(){
  Serial.print(" npulse "); 
  Serial.print(minni.Data30002.npulse);
  Serial.print("  sPeriod ");
  Serial.print(minni.Data30002.sPeriod);
  Serial.println();
/*  
  display.drawString(0,22,"npulse: " + String(minni.Data30002.npulse));
  display.drawString(0,33,"sPeriod: " + String(minni.Data30002.sPeriod));
  display.clear();
*/
//  Transmission to the Internet Server
      if(TrasmettiAda){
           npulse->    save(minni.Data30002.npulse);
           sPeriod->    save(minni.Data30002.sPeriod);
           Serial.println("Inviato a Adafruit");           
      }
}
