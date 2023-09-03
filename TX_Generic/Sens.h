//  DHT22

#include "DHT.h"
#define PINdata 6       // DHT22 data pin
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
 DHT  dht(PINdata,DHTTYPE) ; // Creats a DHT object
