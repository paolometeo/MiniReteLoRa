// put here instructions for reading sensors

void ReadSensor() {

  //  sensor DHT22
 float t = dht.readTemperature(); // Gets the values of the temperature
 float h = dht.readHumidity(); // Gets the values of the humidity
    minni.Data30003.Humi = h;
    minni.Data30003.Temp = t;
    if(ECHO){    
    // Now print the values:
    Serial.println("Humidity: " + String(minni.Data30003.Humi, 1) + " %");
    Serial.println("Temp (C): " + String(minni.Data30003.Temp, 1) + " deg C");
    }
}
