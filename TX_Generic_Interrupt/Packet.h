//  30002;    Vibration Sensor        byte 8 + 4; 
uint16_t ID_TX = 30002;
uint16_t Length = 12;

typedef struct packet30002{
uint16_t       npulse;   //  number of pulses
uint16_t       sPeriod;  //  time interval in seconds in which it counts pulses
};


//  these declarations must not be changed
 typedef union pluto {
  packet30002 Data30002;            //  Dataxxxxx is the name of the structure to be joined to bufVar
  byte bufVar[MXVAR];               //  array of bytes to be joined with the structure
};
pluto minni;                       //  minni is the name of the union type pluto
