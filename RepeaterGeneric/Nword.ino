/*  Trasforma un numero float    in un 
    numero intero (word) arrotondato
*/
uint16_t Nword(float x) {
  uint16_t h;
  if(x >= 0) {
   h = word(x + 0.5); 
}
  if(x < 0){ 
  h = word(x - 0.5);
}
return h;
}
