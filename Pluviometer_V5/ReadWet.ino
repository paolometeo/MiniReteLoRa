// Sensors return  1 if they are dry,  0  if they are wet
// WetFlg is 1 if any sensors is wet
void ReadWet(){
  wdt_reset();
  WetFlg = 0;
  minni.Data12140.WetnessA = digitalRead(WetPinA);
  minni.Data12140.WetnessB = digitalRead(WetPinB);
 
  if(!minni.Data12140.WetnessA || !minni.Data12140.WetnessB )WetFlg = 1;
  if(ECHO){
    Serial.print("WetnessA ");Serial.println(minni.Data12140.WetnessA);
    Serial.print("WetnessB ");Serial.println(minni.Data12140.WetnessB);
  }
}
