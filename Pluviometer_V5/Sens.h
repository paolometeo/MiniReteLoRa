#define  PluvioPin  5  // Rain gauge
#define  WetPinA     A1  // Wetness sensor A
#define  WetPinB     A2  // Wetness sensor B

byte WetFlg = 0;
int PluvioFactor = 2;  // 0.1 mm for every pulse from rain gauge
