//  12140;    Pluviometer        byte 8 + 8; 
uint16_t ID_TX = 12140;
uint16_t Length = 16;

typedef struct packet12140{
uint16_t       npulse;       //  number of pulses from Rain Gauge
uint16_t       Per;          //  Period of time (s) in which pulses are counted
uint16_t       Irain;        //  rain intensity in 0.1 mm/min
uint8_t       WetnessA;         //  value from wetness sensor A
uint8_t       WetnessB;         //  value from wetness sensor B
};


//  these declarations must not be changed
 typedef union pluto {
  packet12140 Data12140;            //  Dataxxxxx is the name of the structure to be joined to bufVar
  byte bufVar[MXVAR];               //  array of bytes to be joined with the structure
};
pluto minni;                       //  minni is the name of the union type pluto
