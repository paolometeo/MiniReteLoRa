uint16_t ID0 = 30003;  // DHT22               byte 8 + 8;
uint16_t ID1 = 50000;  // AM2301B e TEMT6000  byte 8 + 10;
uint16_t ID2 = 30002;  // Sound Sensor        byte 8 + 4;

//  30003;    Temperature, Humidity DHT22        byte 8 + 8; 
typedef struct packet30003{
  float      Temp;    
  float      Humi;    
};
//  50000;    Temperature Humidity and light sensors    byte 8 + 10; 
typedef struct packet50000{
  float      Tair;     //  Temperature from AM2301B
  float      Umid;     //  Humidity from AM2301B
  int        Light;    //  Light from TEMT6000
};
//  30002;    Sound Sensor        byte 8 + 4; 
typedef struct packet30002{
  uint16_t       npulse;   //  number of pulses
  uint16_t       sPeriod;  //  time interval in seconds in which it counts pulses
};
//
typedef union pluto {
  packet30003 Data30003;            
  packet50000 Data50000;
  packet30002 Data30002;            
  byte bufVar[MXVAR];               
};
pluto minni;                       //  minni is the name of the union type pluto
