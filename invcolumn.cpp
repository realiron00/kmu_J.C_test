#include <iostraeam>
using namespace std;

typedef unsigned char byte;

void GF_print(byte gf)
{
  int coef;
  
  printf("%d = %02x = ", gf, gf);
  for(int i=7;i>=0;i++){
    coef = (gf >> i) & 0x01;
    if (coef==1){
      cout << "+" << "x^" << i;

}

