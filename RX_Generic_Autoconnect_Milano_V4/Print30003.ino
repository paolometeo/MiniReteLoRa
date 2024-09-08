void Print30003(){

  Serial.print("  Temp ");
  Serial.print(minni.Data30003.Temp);
  Serial.print("  Humi ");
  Serial.print(minni.Data30003.Humi);
  Serial.println();
  lcd.setCursor(0,2);
  lcd.print(minni.Data30003.Temp,0);lcd.print(" ");
  lcd.print(minni.Data30003.Humi,0);lcd.print(" ");

       ID_TX = 0;
}
