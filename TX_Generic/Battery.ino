uint16_t Battery(){
//  Read the battery voltage in mV
word outanalog = analogRead(VBATPIN);
//Serial.println(outanalog);
float measuredvbat = 3300.0 * 2 * float(outanalog)/1023.0;
return Nword(measuredvbat);
}
