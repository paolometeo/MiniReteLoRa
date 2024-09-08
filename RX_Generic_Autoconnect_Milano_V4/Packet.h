
uint16_t ID1 = 49001;  // Grassano landslave sensor #1  16 byte + 8
uint16_t ID2 = 49002;  // Grassano landslave sensor #2  16 byte + 8
uint16_t ID3 = 49003;  // Grassano landslave sensor #3  16 byte + 8
uint16_t ID4 = 49004;  // Milano landslave sensor #4  16 byte + 8
uint16_t ID5 = 49010;  // Grassano ripetitor status     10 byte  from rip
uint16_t ID6 = 41001;  // Contaimpulsi RP2024    12 byte  
uint16_t ID7 = 30003;  // Contaimpulsi RP2024    12 byte  

//
uint16_t arrived_49001 = 0;
uint16_t arrived_49002 = 0;
uint16_t arrived_49003 = 0;
uint16_t arrived_49004 = 0;
uint16_t arrived_49010 = 0;

// Stato del ripetitore
struct packet49010{
uint16_t  stato;
};
AdafruitIO_Feed *StatoRip = io.feed("StatoRip");
AdafruitIO_Feed *RSSIrip =  io.feed("RSSIrip");
AdafruitIO_Feed *BATTERYrip =  io.feed("BATTERYrip");
AdafruitIO_Feed *NPACKETrip =  io.feed("NPACKETrip");
AdafruitIO_Feed *arrived10 =     io.feed("arrived10");

typedef struct packet49001{
uint16_t      npulse_1;   
uint16_t      speriod_1;
float         degree_1;
float         degreeMA_1;
float         degreeSD_1;

};
AdafruitIO_Feed *nPulse1 =   io.feed("nPulse1");
AdafruitIO_Feed *sPeriod1 =  io.feed("sPeriod1");
AdafruitIO_Feed *degree1 =   io.feed("degree1");
AdafruitIO_Feed *degreeMA1 = io.feed("degreeMA1");
AdafruitIO_Feed *degreeSD1 = io.feed("degreeSD1");
AdafruitIO_Feed *NPACKET1 =  io.feed("NPACKET1");
AdafruitIO_Feed *BATTERY1 =  io.feed("BATTERY1");
AdafruitIO_Feed *RSSI1 =     io.feed("RSSI1");
AdafruitIO_Feed *arrived1 =     io.feed("arrived1");

typedef struct packet49002{
uint16_t      npulse_2;   
uint16_t      speriod_2;
float         degree_2;
float         degreeMA_2;
float         degreeSD_2;
};
AdafruitIO_Feed *nPulse2 =   io.feed("nPulse2");
AdafruitIO_Feed *sPeriod2 =  io.feed("sPeriod2");
AdafruitIO_Feed *degree2 =   io.feed("degree2");
AdafruitIO_Feed *degreeMA2 = io.feed("degreeMA2");
AdafruitIO_Feed *degreeSD2 = io.feed("degreeSD2");
AdafruitIO_Feed *NPACKET2 =  io.feed("NPACKET2");
AdafruitIO_Feed *BATTERY2 =  io.feed("BATTERY2");
AdafruitIO_Feed *RSSI2 =     io.feed("RSSI2");
AdafruitIO_Feed *arrived2 =     io.feed("arrived2");

typedef struct packet49003{
uint16_t      npulse_3;   
uint16_t      speriod_3;
float         degree_3;
float         degreeMA_3;
float         degreeSD_3;
};
AdafruitIO_Feed *nPulse3 =   io.feed("nPulse3");
AdafruitIO_Feed *sPeriod3 =  io.feed("sPeriod3");
AdafruitIO_Feed *degree3 =   io.feed("degree3");
AdafruitIO_Feed *degreeMA3 = io.feed("degreeMA3");
AdafruitIO_Feed *degreeSD3 = io.feed("degreeSD3");
AdafruitIO_Feed *NPACKET3 =  io.feed("NPACKET3");
AdafruitIO_Feed *BATTERY3 =  io.feed("BATTERY3");
AdafruitIO_Feed *RSSI3 =     io.feed("RSSI3");
AdafruitIO_Feed *arrived3 =     io.feed("arrived3");

typedef struct packet49004{
uint16_t      npulse_4;   
uint16_t      speriod_4;
float         degree_4;
float         degreeMA_4;
float         degreeSD_4;
};
AdafruitIO_Feed *nPulse4 =   io.feed("nPulse4");
AdafruitIO_Feed *sPeriod4 =  io.feed("sPeriod4");
AdafruitIO_Feed *degree4 =   io.feed("degree4");
AdafruitIO_Feed *degreeMA4 = io.feed("degreeMA4");
AdafruitIO_Feed *degreeSD4 = io.feed("degreeSD4");
AdafruitIO_Feed *NPACKET4 =  io.feed("NPACKET4");
AdafruitIO_Feed *BATTERY4 =  io.feed("BATTERY4");
AdafruitIO_Feed *RSSI4 =     io.feed("RSSI4");
AdafruitIO_Feed *arrived4 =  io.feed("arrived4");
AdafruitIO_Feed *nrestart =  io.feed("nrestart");
//
//  41001;    Prova contaimpulsi con RP2024     byte 8 + 4; 

typedef struct packet41001{
float          BMEtemp;
float          BMEhum;
float          BMEpres;  
uint16_t       npulse2024_1;   
uint16_t       npulse2024_2;   
uint16_t       speriod2024;   
};
AdafruitIO_Feed *NPULSE2024_1 =   io.feed("NPULSE2024_1");
AdafruitIO_Feed *NPULSE2024_2 =   io.feed("NPULSE2024_2");
AdafruitIO_Feed *SPERIOD2024 =   io.feed("SPERIOD2024");
AdafruitIO_Feed *BMETEMP =   io.feed("BMETEMP");
AdafruitIO_Feed *BMEHUM =   io.feed("BMEHUM");
AdafruitIO_Feed *BMEPRES =   io.feed("BMEPRES");

//  30003;    DHT22        byte 8 + 8; 
typedef struct packet30003{
float      Temp;    
float      Humi;    
};


typedef union pluto {
  packet41001 Data41001; 
  packet49001 Data49001; 
  packet49002 Data49002;            
  packet49003 Data49003;            
  packet49004 Data49004;            
  packet49010 Data49010;           
  packet30003 Data30003;         
   byte bufVar[MXVAR];               
};
pluto minni;                       //  minni is the name of the union type pluto
