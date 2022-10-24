//  Sound Sensor
void Print30002(){
  int mV = Battery();
  Serial.print(" Batteria RX ");Serial.println(mV);
  Serial.print(" npulse "); 
  Serial.print(minni.Data30002.npulse);
  Serial.print("  sPeriod ");
  Serial.print(minni.Data30002.sPeriod);
  Serial.println();
  display.setCursor(0,22);
  display.print("npulse: "); display.print(minni.Data30002.npulse);
  display.setCursor(0,33);
  display.print("sPeriod: "); display.print(minni.Data30002.sPeriod);   
  display.display();
}
