//  Temp, Humid. and light AM2301B
void Print50000(){
         Serial.print(" Tair "); 
         Serial.print(minni.Data50000.Tair);
         Serial.print("  Humi ");
         Serial.print(minni.Data50000.Umid);
         Serial.print("  Light ");
         Serial.print(minni.Data50000.Light);
         Serial.println();
         display.setCursor(0,22);
         display.print("Tair: "); display.print(minni.Data50000.Tair);
         display.setCursor(0,33);
         display.print("Umid: "); display.print(minni.Data50000.Umid);
         display.display();
}