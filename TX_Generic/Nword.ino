/*  Trasforma un numero float    in un 
    numero intero (word) arrotondato
*/
word Nword(float x) {
  word h;
  if(x >= 0) {
   h = word(x + 0.5); 
}
  if(x < 0){ 
  h = word(x - 0.5);
}
return h;
}
