#define  interruptPin  2  //  The sensor must be connected to this pin
volatile uint16_t n   = 0;
float Tempo       = 0;
float TimeOld     = 0;
uint32_t Period      = 3000;
