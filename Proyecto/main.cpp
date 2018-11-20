#include <bits/stdc++.h>

using namespace std;

enum Tipo {PEON_N, PEON_U, CABALLO, REINA, REY, TORRE, VACIO};

struct pieza {
  Tipo Pieza;
  bool Color;
};

pieza **tablero= new pieza* [8];

int mover(){

}

int main(){

    for (int i=0;i<8;i++) {
        tablero[i]=new pieza[8];
    }

  return 0;
}
