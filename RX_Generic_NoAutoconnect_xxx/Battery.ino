uint16_t Battery(){
//  Read the battery voltage in mV
word outanalog = analogRead(VBAT);
float measuredvbat = 3300.0 * 2 * float(outanalog)/4095.0;
uint16_t mV = measuredvbat;
return mV;
}
