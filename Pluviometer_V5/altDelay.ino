void altDelay(long Period2){
     long TimePassed2 = 0;
     long TimeOld2 = 0;
     long Per2 = Period2;
       TimeOld2 = millis();
       TimePassed2= 0.0;
       while(TimePassed2 < Per2){
         TimePassed2 = millis()-TimeOld2;
         wdt_reset();
       }
}
