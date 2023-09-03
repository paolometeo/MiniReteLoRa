//  30003;    DHT22        byte 8 + 8; 
uint16_t ID_TX = 30003;
uint16_t Length = 16;

typedef struct packet30003{
float      Temp;    
float      Humi;    
};

//  these declarations must not be changed
 typedef union pluto {
  packet30003 Data30003;            //  Dataxxxxx is the name of the structure to be joined to bufVar
  byte bufVar[MXVAR];               //  array of bytes to be joined with the structure
};
pluto minni;                       //  minni is the name of the union type pluto
