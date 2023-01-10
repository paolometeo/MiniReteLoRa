//  it reads PluvioPin and counts the pulse for Period ms 
// it returns: 
//  "n" and "minni.Data12140.npulse" :  number of pulse from Rain Gauge 
//
void ReadPluvio(){
     long TemPass = 0;
     byte stato = 1;
     long TemOld = millis();
     while(TemPass < Period){
        TemPass = millis() - TemOld;
        stato = digitalRead(PluvioPin);
        wdt_reset();        
        if(!stato){
           n++;
           altDelay(500);
        }
     }
     minni.Data12140.npulse = n;
}
