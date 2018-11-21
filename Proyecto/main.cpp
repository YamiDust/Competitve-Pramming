#include <bits/stdc++.h>

using namespace std;

enum Tipo {PEON_N, PEON_U, CABALLO, REINA, REY, TORRE, VACIO,ALFIL};

struct pieza {
  Tipo Pieza;
  bool Color;
};

bool checaMate(pieza **tablero,bool col){
    int x,y;
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            if (tablero[i][j].Pieza==REY && tablero[i][j].Color==col) {
                x=i;
                y=j;
            }
        }
    }

    ///Horizontal
    for (int i=x+1;i<8;i++) {
        if ((tablero[i][y].Pieza==REINA || tablero[i][y].Pieza==TORRE) && tablero[i][y].Color!=col){
            return true;
        }
        if (tablero[i][y].Pieza!=VACIO)
            break;
    }

    for (int i=x-1;i>=0;i--) {
        if ((tablero[i][y].Pieza==REINA || tablero[i][y].Pieza==TORRE) && tablero[i][y].Color!=col){
            return true;
        }
        if (tablero[i][y].Pieza!=VACIO)
            break;
    }

    for (int i=x-1;i>=0;i--) {
        if ((tablero[x][i].Pieza==REINA || tablero[x][i].Pieza==TORRE) && tablero[x][i].Color!=col){
            return true;
        }
        if (tablero[x][i].Pieza!=VACIO)
            break;
    }

    for (int i=x+1;i<8;i++) {
        if ((tablero[x][i].Pieza==REINA || tablero[x][i].Pieza==TORRE) && tablero[x][i].Color!=col){
            return true;
        }
        if (tablero[x][i].Pieza!=VACIO)
            break;
    }

    ///Diagonal
    for (int i=x+1,j=y+1;j<8 && i<8;j++,i++) {
        if ((tablero[i][j].Pieza==REINA || tablero[i][j].Pieza==ALFIL) && tablero[i][j].Color!=col) {
            return true;
        }
        if (tablero[i][j].Pieza!=VACIO)
            break;
    }

    for (int i=x-1,j=y-1;j>=0 && i>=0;j--,i--) {
        if ((tablero[i][j].Pieza==REINA || tablero[i][j].Pieza==ALFIL) && tablero[i][j].Color!=col) {
            return true;
        }
        if (tablero[i][j].Pieza!=VACIO)
            break;
    }

    for (int i=x+1,j=y-1;j>=0 && i<8;j--,i++) {
        if ((tablero[i][j].Pieza==REINA || tablero[i][j].Pieza==ALFIL) && tablero[i][j].Color!=col) {
            return true;
        }
        if (tablero[i][j].Pieza!=VACIO)
            break;
    }

    for (int i=x-1,j=y+1;j<8 && i>=0;j++,i--) {
        if ((tablero[i][j].Pieza==REINA || tablero[i][j].Pieza==ALFIL) && tablero[i][j].Color!=col) {
            return true;
        }
        if (tablero[i][j].Pieza!=VACIO)
            break;
    }

    ///PEONES
    if (col) {
        if (x+1<8 && y+1<8 && (tablero[x+1][y+1].Pieza==PEON_N || tablero[x+1][y+1].Pieza==PEON_U) && tablero[x+1][y+1].Color!=col) {
            return true;
        }
        if (x+1<8 && y-1>=0 && (tablero[x+1][y-1].Pieza==PEON_N || tablero[x+1][y-1].Pieza==PEON_U) && tablero[x+1][y-1].Color!=col) {
            return true;
        }
    }
    else {
        if (x-1>=0 && y+1<8 && (tablero[x-1][y+1].Pieza==PEON_N || tablero[x-1][y+1].Pieza==PEON_U) && tablero[x-1][y+1].Color!=col) {
            return true;
        }
        if (x-1>=0 && y-1>=0 && (tablero[x-1][y-1].Pieza==PEON_N || tablero[x-1][y-1].Pieza==PEON_U) && tablero[x-1][y-1].Color!=col) {
            return true;
        }
    }

    ///CABALLOS
    if (x+1<8 & y+2<8 && tablero[x+1][y+2].Pieza==CABALLO && tablero[x+1][y+2].Color!=col) {
        return true;
    }
    if (x+2<8 & y+1<8 && tablero[x+2][y+1].Pieza==CABALLO && tablero[x+2][y+1].Color!=col) {
        return true;
    }
    if (x+2<8 & y-1>=0 && tablero[x+2][y-1].Pieza==CABALLO && tablero[x+2][y-1].Color!=col) {
        return true;
    }
    if (x+1<8 & y-2>=0 && tablero[x+1][y-2].Pieza==CABALLO && tablero[x+1][y-2].Color!=col) {
        return true;
    }
    if (x-1>=0 & y-2>=0 && tablero[x-1][y-2].Pieza==CABALLO && tablero[x-1][y-2].Color!=col) {
        return true;
    }
    if (x-2>=0 & y-1>=0 && tablero[x-2][y-1].Pieza==CABALLO && tablero[x-2][y-1].Color!=col) {
        return true;
    }
    if (x-2>=0 & y+1<8 && tablero[x-2][y+1].Pieza==CABALLO && tablero[x-2][y+1].Color!=col) {
        return true;
    }
    if (x-1>=0 & y+2<8 && tablero[x-1][y+2].Pieza==CABALLO && tablero[x-1][y+2].Color!=col) {
        return true;
    }

    return false;
}

int mover(){

}

int main(){
    pieza **tablero= new pieza* [8];

    for (int i=0;i<8;i++) {
        tablero[i]=new pieza[8];
    }

    return 0;
}
