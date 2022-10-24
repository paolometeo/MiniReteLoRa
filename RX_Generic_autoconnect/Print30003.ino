// DHT 22
void Print30003(){
         Serial.print(" Temp "); 
         Serial.print(minni.Data30003.Temp);
         Serial.print("  Humi ");
         Serial.print(minni.Data30003.Humi);
         Serial.println();
         display.setCursor(0,22);
         display.print("Temp: "); display.print(minni.Data30003.Temp);
         display.setCursor(0,33);
         display.print("Humi "); display.print(minni.Data30003.Humi);
         display.display();      
}
