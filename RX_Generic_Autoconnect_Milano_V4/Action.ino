void Action(){

//  Identification and re-transmission 
         if(ID_TX == ID1){
              Print49001();
         }else if(ID_TX == ID2){
              Print49002();
         }else  if(ID_TX == ID3){
              Print49003();
         }else  if(ID_TX == ID4){
              Print49004();
         }else  if(ID_TX == ID5){
              Print49010();
         }else  if(ID_TX == ID6){
              Print41001();
        }else  if(ID_TX == ID7){
              Print30003();
         }else{
               Serial.println(" ID_TX not permitted ");
         }
         for(int i = 0; i < MXVAR; i++){
            minni.bufVar[i] = 0;
         }         
  }
