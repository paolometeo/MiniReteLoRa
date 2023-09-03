#define MXbuf      400
#define MXVAR      400
byte      Roger   = 0;
byte      len     = 0;  
uint16_t  ID_TX   = 0;       //  TX ID received from message header
uint16_t  Length  = 0;       //  message Length from TX header
uint16_t  npacket = 0;       //  message number from TX header
uint16_t  vBatTX  = 0;      //   Battery voltage from TX header
uint16_t  nRSSI   = 0;      //  received RSSI
byte      buf[MXbuf];

