//  TX   12127;  
uint16_t ID_TX = 0;
uint16_t ID1 = 12127;
//  RIP  12128
uint16_t ID_RIP = 12128;
uint16_t Length = 36;  // payload Length  for 12127 and 12128 + 28
//
// Same structure as TX message
struct packet12127{
float  Volt1;   
float  Volt2;   
float  curr1;   
float  curr2;   
float  T1;
float  T2;
float  T3;
};

uint16_t LengthRIP = 10;  // payload Length  8 + 2
//
struct packet12129{
uint16_t  stato;  // = 1: all is ok; = 2: no messages from TX at the setup; = 3: no messages from TX at the loop
};
//
union pluto {
  packet12127 Data12127;            
  packet12129 Data12129;            
  byte bufVar[MXVAR];               
};
pluto minni;            
