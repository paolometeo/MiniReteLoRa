uint16_t ID0 = 12127;  // solar panel
uint16_t ID1 = 12130;  // Barcellona dust sensor
uint16_t ID2 = 12140;  // Solar panel
uint16_t ID3 = 30002;  // Sound sensor
uint16_t ID4 = 30003;  // DHT22   
uint16_t ID5 = 40004;  // DHT22   
uint16_t ID6 = 50000;  // CREA sensor   

//  Solar Test Panel
typedef struct packet12127{
float  curr1;   //  corrente in mA da ina1  batteria
float  curr2;   //  corrente in mA da ina2  FV
float  Volt1;   //  tensione della batteria
float  Volt2;   //  tensione del FV
};
AdafruitIO_Feed *curr1 = io.feed("CorBat");
AdafruitIO_Feed *curr2 = io.feed("CorFV");
AdafruitIO_Feed *Volt1 = io.feed("VoltBat");
AdafruitIO_Feed *Volt2 = io.feed("VoltFV");

//  Dust sensor (Perlongo)
typedef struct packet12130{
float      Conc25;   
float      Conc10;
float      UMID;    
float      TEMP;    
};
AdafruitIO_Feed *Conc25 = io.feed("Conc25");
AdafruitIO_Feed *Conc10 = io.feed("Conc10");
AdafruitIO_Feed *UMID = io.feed("UMID");
AdafruitIO_Feed *TEMP = io.feed("TEMP");

//  Rain gauge (Perlongo)
typedef struct packet12140{
uint16_t       npulse;       //  number of pulses from Rain Gauge
uint16_t       Per;          //  Period of time (s) in which pulses are counted
uint16_t       Irain;        //  rain intensity in 0.1 mm/min
uint8_t       WetnessA;         //  value from wetness sensor A
uint8_t       WetnessB;         //  value from wetness sensor B

};
AdafruitIO_Feed *n = io.feed("n");
AdafruitIO_Feed *Per = io.feed("Per");
AdafruitIO_Feed *Irain = io.feed("Irain");
AdafruitIO_Feed *WetnessA = io.feed("WetnessA");
AdafruitIO_Feed *WetnessB = io.feed("WetnessB");
AdafruitIO_Feed *npack = io.feed("npack");
AdafruitIO_Feed *Bat = io.feed("Battery");
AdafruitIO_Feed *RainH = io.feed("RainH");

//  30002;    Sound Sensor        byte 8 + 4; 
typedef struct packet30002{
  uint16_t       npulse;   //  number of pulses
  uint16_t       sPeriod;  //  time interval in seconds in which it counts pulses
};
AdafruitIO_Feed *npulse = io.feed("npulse");
AdafruitIO_Feed *sPeriod = io.feed("sPeriod");

//  30003;    Temperature, Humidity DHT22        byte 8 + 8; 
typedef struct packet30003{
  float      Temp;    
  float      Humi;    
};
AdafruitIO_Feed *Temp = io.feed("Temp");
AdafruitIO_Feed *Humi = io.feed("Humi");


typedef struct packet40004{
float      Temperature;    
float      Humidity;
};
AdafruitIO_Feed *Temperature = io.feed("Temperature");
AdafruitIO_Feed *Humidity = io.feed("Humidity");

//  50000;    Temperature Humidity and light sensors    byte 8 + 10; 
typedef struct packet50000{
  float      Tair;     //  Temperature from AM2301B
  float      Umid;     //  Humidity from AM2301B
  int        Light;    //  Light from TEMT6000
};
AdafruitIO_Feed *Tair = io.feed("Tair");
AdafruitIO_Feed *Umid = io.feed("Umid");
AdafruitIO_Feed *Light = io.feed("Light");

//
typedef union pluto {
  packet12127 Data12127;            
  packet12130 Data12130;            
  packet12140 Data12140;            
  packet30002 Data30002;            
  packet30003 Data30003;
  packet40004 Data40004;
  packet50000 Data50000;            
  byte bufVar[MXVAR];               
};
pluto minni;                       //  minni is the name of the union type pluto

// AdafruitIO declarations
