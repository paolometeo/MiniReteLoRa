///////////////////////////////////////////////////////
byte PushButt(long timeOut){
// Aspetta fino a timeOut ms che venga premuto il pulsante.  
// Esce 1 se il pulsante è stato premuto, 0 altrimenti
// Se timeOut = 0 aspetta sempre

     byte flg = 0;
     byte Status = 1;
     long timeOld = 0;
     long timePassed = 0;
     Serial.print("timeOut ");Serial.println(timeOut);
     if(timeOut == 0){
       while(1){
          Status = digitalRead(TRIGGER_PIN);
          Serial.print(" Status ");Serial.println(Status);
          if(Status == 0){
            flg = 1;    // ha premuto il pulsante
            return flg;
          }
       }
     }else{
 //    
     timeOld = millis();
     while(1){
         Status = digitalRead(TRIGGER_PIN);
         if(Status == 0){
            flg = 1;    // ha premuto il pulsante
            break;
         }
         timePassed = millis()-timeOld;
         if(timePassed > timeOut){
            flg = 0;     //  non ha premuto il pulsante entro 5 s
            break;
         }
      }
      return flg;
     }
}
