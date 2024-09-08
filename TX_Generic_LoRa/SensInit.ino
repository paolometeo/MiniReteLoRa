//  put here instructions for initializing sensors 
void SensInit(){
    Wire.begin();
  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }
  
  bme.begin();
}
