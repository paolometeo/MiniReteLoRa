void Action(){

//  Identification and re-transmission 
         if(ID_TX == ID1 || ID_TX == ID2){
              Print12127();
          }else{
               Serial.println(" ID_TX not permitted ");
         }
         for(int i = 0; i < MXVAR; i++){
            minni.bufVar[i] = 0;
         }         
  }
