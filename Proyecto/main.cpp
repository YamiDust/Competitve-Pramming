#include <bits/stdc++.h>

using namespace std;

enum Tipo {PEON_N, PEON_U, CABALLO, REINA, REY, TORRE, VACIO,ALFIL};

struct pieza {
  Tipo Pieza;
  bool Color;
};

pieza **tablero= new pieza* [8];

void inicio(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            tablero[i][j].Pieza=VACIO;
            tablero[i][j].Color=1;
        }
    }
    for(int i=0;i<8;i++){
        tablero[6][i].Pieza = PEON_N;
        tablero[6][i].Color = 0;
        tablero[1][i].Pieza = PEON_N;
        tablero[1][i].Color = 1;
    }

    tablero[0][0].Pieza = TORRE;
    tablero[0][0].Color = 1;
    tablero[0][1].Pieza = CABALLO;
    tablero[0][1].Color = 1;
    tablero[0][2].Pieza = ALFIL;
    tablero[0][2].Color = 1;
    tablero[0][3].Pieza = REINA;
    tablero[0][3].Color = 1;
    tablero[0][4].Pieza = REY;
    tablero[0][4].Color = 1;
    tablero[0][5].Pieza = ALFIL;
    tablero[0][5].Color = 1;
    tablero[0][6].Pieza = CABALLO;
    tablero[0][6].Color = 1;
    tablero[0][7].Pieza = TORRE;
    tablero[0][7].Color = 1;
    tablero[7][0].Pieza = TORRE;
    tablero[7][0].Color = 0;
    tablero[7][1].Pieza = CABALLO;
    tablero[7][1].Color = 0;
    tablero[7][2].Pieza = ALFIL;
    tablero[7][2].Color = 0;
    tablero[7][3].Pieza = REINA;
    tablero[7][3].Color = 0;
    tablero[7][4].Pieza = REY;
    tablero[7][4].Color = 0;
    tablero[7][5].Pieza = ALFIL;
    tablero[7][5].Color = 0;
    tablero[7][6].Pieza = CABALLO;
    tablero[7][6].Color = 0;
    tablero[7][7].Pieza = TORRE;
    tablero[7][7].Color = 0;

}

void imprime_tablero(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(tablero[i][j].Pieza == PEON_N){
                cout << 1;
            }
            if(tablero[i][j].Pieza == TORRE){
                cout << 2;
            }
            if(tablero[i][j].Pieza == CABALLO){
                cout << 3;
            }
            if(tablero[i][j].Pieza == ALFIL){
                cout << 4;
            }
            if(tablero[i][j].Pieza == REINA){
                cout << 5;
            }
            if(tablero[i][j].Pieza == REY){
                cout << 6;
            }
            if(tablero[i][j].Pieza == VACIO){
                cout << 0;
            }
            cout << tablero[i][j].Color << " ";
        }
        cout << "\n";
  }
}

bool checaMate(pieza **tablero,bool col, int x, int y){

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

    for (int i=y-1;i>=0;i--) {
        if ((tablero[x][i].Pieza==REINA || tablero[x][i].Pieza==TORRE) && tablero[x][i].Color!=col){
            return true;
        }
        if (tablero[x][i].Pieza!=VACIO)
            break;
    }

    for (int i=y+1;i<8;i++) {
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

int valor(bool nelson, pieza a){
    if(!nelson)return 0;
    if(a.Pieza == PEON_N || a.Pieza == PEON_U) return 1;
    if(a.Pieza == CABALLO || a.Pieza == ALFIL) return 3;
    if(a.Pieza == REINA) return 10;
    if(a.Pieza == TORRE) return 5;
    if(a.Pieza == REY) return 100000;
}

int peso(pieza **tablero){
    int pos=0,  neg=0,  pnt;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(tablero[i][j].Pieza != VACIO){
                if(tablero[i][j].Color){
                    pnt+= valor(!checaMate(tablero,tablero[i][j].Color,i,j), tablero[i][j]);
                }
                else {
                    pnt+= valor(checaMate(tablero,tablero[i][j].Color,i,j), tablero[i][j]);
                }
            }
        }
    }
    return pnt;
}

int main(){
    //pieza **tablero= new pieza* [8];

    for (int i=0;i<8;i++) {
        tablero[i]=new pieza[8];
    }
    inicio();
    imprime_tablero();

    return 0;
}
