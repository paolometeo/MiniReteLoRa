void ReadSensor() {
 float t = dht.readTemperature(); // Gets the values of the temperature
 float h = dht.readHumidity(); // Gets the values of the humidity
   // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

    minni.Data30003.Humi = h;
    minni.Data30003.Temp = t;
    if(ECHO){    
    // Now print the values:
    Serial.println("Humidity: " + String(minni.Data30003.Humi, 1) + " %");
    Serial.println("Temp (C): " + String(minni.Data30003.Temp, 1) + " deg C");
    }
}
