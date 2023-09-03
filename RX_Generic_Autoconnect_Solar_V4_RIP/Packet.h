uint16_t ID2 = 12128;  // ripetitore sulla banda 2
uint16_t ID1 = 12127;  // TX sulla banda 1
//
struct packet12127{
float  Volt1;   //  tensione media della batteria
float  Volt2;   //  tensione media del FV
float  curr1;   //  corrente media in mA da ina1  batteria
float  curr2;   //  corrente media in mA da ina2  FV
float  T1;
float  T2;
float  T3;
};
AdafruitIO_Feed *curr1 = io.feed("CorBat");
AdafruitIO_Feed *curr2 = io.feed("CorFV");
AdafruitIO_Feed *Volt1 = io.feed("VoltBat");
AdafruitIO_Feed *Volt2 = io.feed("VoltFV");
AdafruitIO_Feed *Power1 = io.feed("Power1");
AdafruitIO_Feed *Power2 = io.feed("Power2");
AdafruitIO_Feed *TT1 = io.feed("Temp1");
AdafruitIO_Feed *TT2 = io.feed("Temp2");
AdafruitIO_Feed *TT3 = io.feed("Temp3");

//  these declarations must not be changed
typedef union pluto {
  packet12127 Data12127;            
  byte bufVar[MXVAR];                        
};
pluto minni;                       //  minni is the name of the union type pluto
