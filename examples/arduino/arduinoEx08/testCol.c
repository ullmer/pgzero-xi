int    getR(int color) {int result = color & 0xff0000; result >>= 16; return result;}
int    getG(int color) {int result = color & 0xff00;   result >>= 8;  return result;}
int    getB(int color) {int result = color & 0xff;                    return result;}

#include <stdio.h>

int main() {

  int color=0x00ffff;
  int r, g, b;
  r = getR(color); g = getG(color); b = getB(color);
  printf("%i %i %i\n", r, g, b);
}

