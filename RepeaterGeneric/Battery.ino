uint16_t Battery(){
//  Read the battery voltage in mV
uint16_t outanalog = analogRead(VBATPIN);
float measuredvbat = 3300.0 * 2 * float(outanalog)/1023.0;
return Nword(measuredvbat);
}
