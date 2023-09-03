void Blinking(){
    for(i=0; i < 10; i++){
      digitalWrite(LEDpin,HIGH);
      altDelay(100);
      digitalWrite(LEDpin,LOW);
      altDelay(100);
  }
  if(LEDpin == 17){
    digitalWrite(LEDpin,HIGH);
  }else{
    digitalWrite(LEDpin,LOW);
  }
}
