void ReadSensor() {
 float t = bme.temp(); // Gets the values of the temperature
 float h = bme.hum(); // Gets the values of the humidity
 float pre = bme.pres();
    minni.Data30003.Humi = h;
    minni.Data30003.Temp = t;
   
    if(ECHO){    
    // Now print the values:
    Serial.println("Humidity: " + String(minni.Data30003.Humi, 1) + " %");
    Serial.println("Temp (C): " + String(minni.Data30003.Temp, 1) + " deg C");
    }
}
