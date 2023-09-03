void altDelay(uint32_t Period){
     float TimePassed = 0;
     float TimeOld2 = 0;
     
     uint32_t Per = Period;
       TimeOld2 = millis();
       TimePassed = millis()-TimeOld2;
       while(TimePassed < Period){
         TimePassed = millis()-TimeOld2;
       }
}
