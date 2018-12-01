#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

enum Tipo {PEON_N, PEON_U, CABALLO, REINA, REY, TORRE, VACIO,ALFIL};

struct pieza {
  Tipo Pieza;
  bool Color;
};

int page=0;
int cont_check=0;
int cont_val=0;
int GLOBAL_COLOR,PLAYER1,PLAYER2;
int best_future,rnd;
pieza **t_best = new pieza* [8];
pieza **tablero = new pieza* [8];
int **color_tablero = new int *[8];
bool enro_der=true;
bool enro_izq=true;
bool awake;
int amd[8][8];
int desde[5][6][2]={ {{0,6},{0,1},{1,3},{1,4},{0,5},{1,7}},   {{1,3},{0,1},{1,5},{0,2},{4,6},{3,7}},   {{0,1},{1,3},{0,2},{0,3},{1,0},{1,7}},   {{0,1},{0,6},{1,3},{0,2},{0,3},{1,6}},   {{0,1},{0,6},{1,1},{0,1},{0,3},{1,3}}   };
int hasta[5][6][2]={ {{2,5},{2,2},{3,3},{2,4},{3,2},{2,7}},   {{3,3},{2,2},{2,5},{4,6},{3,7},{1,5}},   {{2,2},{3,3},{2,4},{0,1},{2,0},{2,7}},   {{2,2},{2,5},{3,3},{2,4},{0,1},{3,6}},   {{2,2},{2,5},{2,1},{1,1},{5,1},{3,3}}   };

void copea(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            t_best[i][j].Pieza=tablero[i][j].Pieza;
            t_best[i][j].Color=tablero[i][j].Color;
        }
    }
}

void copea2(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            tablero[i][j].Pieza=t_best[i][j].Pieza;
            tablero[i][j].Color=t_best[i][j].Color;
        }
    }
}

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
            if(tablero[i][j].Pieza == PEON_N || tablero[i][j].Pieza == PEON_U){
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
  cout << "\n";
}

void imprime_t(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(t_best[i][j].Pieza == PEON_N || t_best[i][j].Pieza == PEON_U){
                cout << 1;
            }
            if(t_best[i][j].Pieza == TORRE){
                cout << 2;
            }
            if(t_best[i][j].Pieza == CABALLO){
                cout << 3;
            }
            if(t_best[i][j].Pieza == ALFIL){
                cout << 4;
            }
            if(t_best[i][j].Pieza == REINA){
                cout << 5;
            }
            if(t_best[i][j].Pieza == REY){
                cout << 6;
            }
            if(t_best[i][j].Pieza == VACIO){
                cout << 0;
            }
            cout << t_best[i][j].Color << " ";
        }
        cout << "\n";
  }
  cout << "\n";
}

int ColorActual(int x, int y){
    x-=30;
    y-=30;
    x/=80;
    y/=80;
    if(x%2!=y%2){
        return WHITE;
    }
    return BLACK;
}

bool checaMate(pieza **tablero,bool col, int x, int y){
    //cout << "ES EN CHECA MATE\n";
    //cout << col <<  "\n";
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

int peso(pieza **tablero,bool col){

    int pos=0,  neg=0,  pnt;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(tablero[i][j].Pieza != VACIO){
                if(tablero[i][j].Color==col){
                    if (checaMate(tablero,tablero[i][j].Color,i,j)) {
                        pnt-=valor(true,tablero[i][j]);
                    }
                    else{
                        pnt+=valor(true,tablero[i][j]);
                    }
                }
                else {
                    pnt+= valor(checaMate(tablero,tablero[i][j].Color,i,j), tablero[i][j]);
                }
            }
        }
    }
    return pnt;
}

void Draw_Board(int **color_tablero){

    //setcolor(BLACK);
    int cont=0;
//    int *rec= new int[8];
//    rec[0]=30;
//    rec[1]=30;
//    rec[2]=30;
//    rec[3]=670;
//    rec[6]=670;
//    rec[7]=30;
//    rec[4]=880;
//    rec[5]=880;
//
//    //setcolor(WHITE);
//
//    setfillstyle(SOLID_FILL,BLACK);
//    fillpoly(4,rec);
    cleardevice();
    setfillstyle(SOLID_FILL,WHITE);
    for(int i=30,I=0;i<670;i+=80,I++){
        for(int j=30,J=0;j<670;j+=80,J++){
                int *ax = new int[8];
                ax[0]=j;
                ax[1]=i;
                ax[2]=j+80;
                ax[3]=i;
                ax[4]=j+80;
                ax[5]=i+80;
                ax[6]=j;
                ax[7]=i+80;
                setfillstyle(SOLID_FILL,color_tablero[I][J]);
                fillpoly(4,ax);
        }
        cont++;
    }
    return;
}

void Draw_Pawn(int y, int x,int clr){

    setfillstyle(SOLID_FILL,clr);
    fillellipse(x+40,y+20,7,7);
    fillellipse(x+40,y+29,7,2);
    arc(x+72,y+30,180,240,30);
    arc(x+8,y+30,300,0,30);
    rectangle(x+20,y+55,x+60,y+63);
    floodfill(x+40,y+50,GLOBAL_COLOR);
    floodfill(x+40,y+58,GLOBAL_COLOR);
}

void Draw_Bishop(int y, int x, int clr){

    setfillstyle(SOLID_FILL,clr);
    fillellipse(x+40,y+30,17,15);
    fillellipse(x+40,y+13,4,4);
    arc(x+70,y+25,210,270,30);
    arc(x+70,y+33,200,270,30);
    arc(x+10,y+25,270,330,30);
    arc(x+10,y+33,270,340,30);
    line(x+9,y+55,x+9,y+63);
    line(x+69,y+55,x+69,y+63);
    floodfill(x+11,y+56,GLOBAL_COLOR);
    floodfill(x+68,y+56,GLOBAL_COLOR);
    rectangle(x+37,y+22,x+43,y+38);
    setfillstyle(SOLID_FILL,ColorActual(x,y));
    floodfill(x+40,y+30,GLOBAL_COLOR);
    rectangle(x+32,y+27,x+48,y+33);
    floodfill(x+33,y+28,GLOBAL_COLOR);
    floodfill(x+47,y+32,GLOBAL_COLOR);

}

void Draw_Rock(int y, int x,int clr){

    setfillstyle(SOLID_FILL,clr);
    y-=5;
    int ax[30]={20,20, 30,20, 30,30, 35,30, 35,20, 45,20, 45,30, 50,30, 50,20, 60,20, 60,35, 50,45, 30,45, 20,35, 20,20};
    for(int i=0;i<30;i+=2){
        ax[i]+=x;
        ax[i+1]+=y;
    }
    drawpoly(15,ax);
    floodfill(x+40,y+40,GLOBAL_COLOR);
    rectangle(x+30,y+45,x+50,y+60);
    floodfill(x+40,y+58,GLOBAL_COLOR);
    line(x+20,y+65,x+30,y+60);
    line(x+60,y+65,x+50,y+60);
    rectangle(x+20,y+65,x+60,y+70);
    floodfill(x+40,y+63,GLOBAL_COLOR);
    floodfill(x+40,y+68,GLOBAL_COLOR);
}

void Draw_Knight(int y, int x,int clr){

    y+=2;
    setfillstyle(SOLID_FILL,clr);
    line(x+20,y+25,x+45,y+10);
    line(x+45,y+10,x+45,y+5);
    line(x+45,y+5,x+50,y+10);
    line(x+50,y+10,x+65,y+15);
    line(x+65,y+15,x+60,y+45);
    line(x+60,y+45,x+50,y+55);
    line(x+35,y+55,x+30,y+45);
    line(x+30,y+45,x+50,y+30);
    line(x+50,y+30,x+25,y+35);
    line(x+25,y+35,x+20,y+25);
    rectangle(x+30,y+55,x+50,y+60);
    rectangle(x+20,y+60,x+60,y+70);
    //arc(x+60,y+55,88,183,10);
    floodfill(x+45,y+50,GLOBAL_COLOR);
    floodfill(x+45,y+57,GLOBAL_COLOR);
    floodfill(x+45,y+65,GLOBAL_COLOR);
    setfillstyle(SOLID_FILL,ColorActual(x,y));
    fillellipse(x+48,y+17,4,4);
    fillellipse(x+25,y+28,2,2);
}

void Draw_Quen(int y, int x,int clr){

    setfillstyle(SOLID_FILL,clr);
    int ax[28]={15,20, 28,35, 30,20, 35,37, 40,20, 45,37, 50,20, 52,35, 65,20, 55,48, 55,65, 25,65, 25,48, 15,20};
    for(int i=0;i<28;i+=2){
        ax[i]+=x;
        ax[i+1]+=y;
    }
    drawpoly(14,ax);
    floodfill(x+40,y+45,GLOBAL_COLOR);
    rectangle(x+25,y+50,x+55,y+60);
    fillellipse(x+15,y+20,4,5);
    fillellipse(x+30,y+20,4,5);
    fillellipse(x+40,y+20,4,5);
    fillellipse(x+50,y+20,4,5);
    fillellipse(x+65,y+20,4,5);
}

void Draw_King(int y, int x,int clr){

    y+=8;
    setfillstyle(SOLID_FILL,clr);
    int ax[24]={40,50, 42,40, 45,30, 51,22, 60,20, 67,22, 70,30, 68,35, 64,40, 60,45, 58,50, 40,50};
    int ay[24];
    for(int i=0;i<24;i+=2){
        ay[i]=x+80-ax[i];
        ay[i+1]=y+ax[i+1];
        ax[i]+=x;
        ax[i+1]+=y;
    }
    drawpoly(12,ax);
    drawpoly(12,ay);
    floodfill(x+55,y+35,GLOBAL_COLOR);
    floodfill(x+25,y+35,GLOBAL_COLOR);
    rectangle(x+20,y+50,x+60,y+60);
    int az[14]={45,30, 42,24, 41,21, 40,20, 39,21, 38,24, 35,30};
    for(int i=0;i<14;i+=2){
        az[i]+=x;
        az[i+1]+=y;
    }
    drawpoly(7,az);
    floodfill(x+40,y+31,GLOBAL_COLOR);
    floodfill(x+40,y+51,GLOBAL_COLOR);

    bar(x+38,y+6,x+42,y+24);
    bar(x+33,y+10,x+47,y+14);
}

void Draw_Game(pieza **tablero){
        setvisualpage(page);
        setactivepage(1-page);

        Draw_Board(color_tablero);
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(tablero[i][j].Pieza!=VACIO){
                    if(tablero[i][j].Pieza==REY){
                        if(tablero[i][j].Color) Draw_King(i*80+30,j*80+30,PLAYER1);
                        else Draw_King(i*80+30,j*80+30,PLAYER2);
                    }
                    if(tablero[i][j].Pieza==REINA){
                        if(tablero[i][j].Color) Draw_Quen(i*80+30,j*80+30,PLAYER1);
                        else Draw_Quen(i*80+30,j*80+30,PLAYER2);
                    }
                    if(tablero[i][j].Pieza==ALFIL){
                        if(tablero[i][j].Color) Draw_Bishop(i*80+30,j*80+30,PLAYER1);
                        else Draw_Bishop(i*80+30,j*80+30,PLAYER2);
                    }
                    if(tablero[i][j].Pieza==CABALLO){
                        if(tablero[i][j].Color) Draw_Knight(i*80+30,j*80+30,PLAYER1);
                        else Draw_Knight(i*80+30,j*80+30,PLAYER2);
                    }
                    if(tablero[i][j].Pieza==TORRE){
                        if(tablero[i][j].Color) Draw_Rock(i*80+30,j*80+30,PLAYER1);
                        else Draw_Rock(i*80+30,j*80+30,PLAYER2);
                    }
                    if(tablero[i][j].Pieza==PEON_N || tablero[i][j].Pieza==PEON_U ){
                        if(tablero[i][j].Color) Draw_Pawn(i*80+30,j*80+30,PLAYER1);
                        else Draw_Pawn(i*80+30,j*80+30,PLAYER2);
                    }
                }
            }
        }
        page=1-page;
        setvisualpage(page);
    }

void Tablero_Color_rst (pieza **tablero, int ** color_tablero) {
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            if (i%2==0) {
                if (j%2==0) {
                    color_tablero[i][j]=BLACK;
                }
                else {
                    color_tablero[i][j]=WHITE;
                }
            }
            else {
                if (j%2==1) {
                    color_tablero[i][j]=BLACK;
                }
                else {
                    color_tablero[i][j]=WHITE;
                }
            }
        }
    }
    return;
}

void Colorear_Casillas (pieza **tablero, int **color_tablero, int x,int y) {
    if (tablero[x][y].Pieza==PEON_N) {
        int i=x,j=y;
        if (tablero[i][j].Color) {
            if (tablero[i+1][j].Pieza==VACIO) {
                color_tablero[i+1][j]=YELLOW;
                if (tablero[i+2][j].Pieza==VACIO) {
                    color_tablero[i+2][j]=YELLOW;
                }
            }
            if (j+1<8 && i+1<8 && tablero[i+1][j+1].Pieza!=VACIO && tablero[i+1][j+1].Color!=tablero[x][y].Color) {
                color_tablero[i+1][j+1]=RED;
            }
            if (j-1>=0 && i+1<8 && tablero[i+1][j-1].Pieza!=VACIO  && tablero[i+1][j-1].Color!=tablero[x][y].Color) {
                color_tablero[i+1][j-1]=RED;
            }
        }
        else {
            if (tablero[i-1][j].Pieza==VACIO) {
                color_tablero[i-1][j]=YELLOW;
                if (tablero[i-2][j].Pieza==VACIO && tablero[i+1][j+1].Pieza!=tablero[x][y].Pieza) {
                    color_tablero[i-2][j]=YELLOW;
                }
            }
            if (j+1<8 && i-1>=0 && tablero[i-1][j+1].Pieza!=VACIO  && tablero[i-1][j+1].Color!=tablero[x][y].Color) {
                color_tablero[i-1][j+1]=RED;
            }
            if (j-1>=0 && i-1>=0 && tablero[i-1][j-1].Pieza!=VACIO  && tablero[i-1][j-1].Color!=tablero[x][y].Color) {
                color_tablero[i-1][j-1]=RED;
            }
        }
    }

    if (tablero[x][y].Pieza==PEON_U) {
        int i=x,j=y;
        if (tablero[i][j].Color) {
            if (i+1<8 && tablero[i+1][j].Pieza==VACIO) {
                color_tablero[i+1][j]=YELLOW;
            }
            if (j+1<8  && i+1<8 && tablero[i+1][j+1].Pieza!=VACIO  && tablero[i+1][j+1].Color!=tablero[x][y].Color) {
                color_tablero[i+1][j+1]=RED;
            }
            if (j-1>=0 && i+1<8 && tablero[i+1][j-1].Pieza!=VACIO  && tablero[i+1][j-1].Color!=tablero[x][y].Color) {
                color_tablero[i+1][j-1]=RED;
            }
        }
        else {
            if (i-1>=0 && tablero[i-1][j].Pieza==VACIO) {
                color_tablero[i-1][j]=YELLOW;
            }
            if (j+1<8  && i-1>=0 && tablero[i-1][j+1].Pieza!=VACIO  && tablero[i-1][j+1].Color!=tablero[x][y].Color) {
                color_tablero[i-1][j+1]=RED;
            }
            if (j-1>=0 && i-1>=0 && tablero[i-1][j-1].Pieza!=VACIO  && tablero[i-1][j-1].Color!=tablero[x][y].Color) {
                color_tablero[i-1][j-1]=RED;
            }
        }
    }

    if (tablero[x][y].Pieza==CABALLO) {
        if (x+1<8 & y+2<8 && tablero[x+1][y+2].Pieza!=VACIO && tablero[x+1][y+2].Color!=tablero[x][y].Color) {
            color_tablero[x+1][y+2]=RED;
        }
        if (x+2<8 & y+1<8 && tablero[x+2][y+1].Pieza!=VACIO && tablero[x+2][y+1].Color!=tablero[x][y].Color) {
            color_tablero[x+2][y+1]=RED;
        }
        if (x+2<8 & y-1>=0 && tablero[x+2][y-1].Pieza!=VACIO && tablero[x+2][y-1].Color!=tablero[x][y].Color) {
            color_tablero[x+2][y-1]=RED;
        }
        if (x+1<8 & y-2>=0 && tablero[x+1][y-2].Pieza!=VACIO && tablero[x+1][y-2].Color!=tablero[x][y].Color) {
            color_tablero[x+1][y-2]=RED;
        }
        if (x-1>=0 & y-2>=0 && tablero[x-1][y-2].Pieza!=VACIO && tablero[x-1][y-2].Color!=tablero[x][y].Color) {
            color_tablero[x-1][y-2]=RED;
        }
        if (x-2>=0 & y-1>=0 && tablero[x-2][y-1].Pieza!=VACIO && tablero[x-2][y-1].Color!=tablero[x][y].Color) {
            color_tablero[x-2][y-1]=RED;
        }
        if (x-2>=0 & y+1<8 && tablero[x-2][y+1].Pieza!=VACIO && tablero[x-2][y+1].Color!=tablero[x][y].Color) {
            color_tablero[x-2][y+1]=RED;
        }
        if (x-1>=0 & y+2<8 && tablero[x-1][y+2].Pieza!=VACIO && tablero[x-1][y+2].Color!=tablero[x][y].Color) {
            color_tablero[x-1][y+2]=RED;
        }

        if (x+1<8 & y+2<8 && tablero[x+1][y+2].Pieza==VACIO) {
            color_tablero[x+1][y+2]=YELLOW;
        }
        if (x+2<8 & y+1<8 && tablero[x+2][y+1].Pieza==VACIO) {
            color_tablero[x+2][y+1]=YELLOW;
        }
        if (x+2<8 & y-1>=0 && tablero[x+2][y-1].Pieza==VACIO) {
            color_tablero[x+2][y-1]=YELLOW;
        }
        if (x+1<8 & y-2>=0 && tablero[x+1][y-2].Pieza==VACIO) {
            color_tablero[x+1][y-2]=YELLOW;
        }
        if (x-1>=0 & y-2>=0 && tablero[x-1][y-2].Pieza==VACIO) {
            color_tablero[x-1][y-2]=YELLOW;
        }
        if (x-2>=0 & y-1>=0 && tablero[x-2][y-1].Pieza==VACIO) {
            color_tablero[x-2][y-1]=YELLOW;
        }
        if (x-2>=0 & y+1<8 && tablero[x-2][y+1].Pieza==VACIO) {
            color_tablero[x-2][y+1]=YELLOW;
        }
        if (x-1>=0 & y+2<8 && tablero[x-1][y+2].Pieza==VACIO) {
            color_tablero[x-1][y+2]=YELLOW;
        }
    }

    if (tablero[x][y].Pieza==REINA || tablero[x][y].Pieza==TORRE) {
        for (int i=x+1;i<8;i++) {
            if (tablero[i][y].Pieza==VACIO) {
                color_tablero[i][y]=YELLOW;
            }
            else {
                if (tablero[i][y].Color!=tablero[x][y].Color) {
                    color_tablero[i][y]=RED;
                }
                break;
            }
        }
        for (int i=x-1;i>=0;i--) {
            if (tablero[i][y].Pieza==VACIO) {
                color_tablero[i][y]=YELLOW;
            }
            else {
                if (tablero[i][y].Color!=tablero[x][y].Color) {
                    color_tablero[i][y]=RED;
                }
                break;
            }
        }

        for (int j=y+1;j<8;j++) {
            if (tablero[x][j].Pieza==VACIO) {
                color_tablero[x][j]=YELLOW;
            }
            else {
                if (tablero[x][j].Color!=tablero[x][y].Color) {
                    color_tablero[x][j]=RED;
                }
                break;
            }
        }
        for (int j=y-1;j>=0;j--) {
            if (tablero[x][j].Pieza==VACIO) {
                color_tablero[x][j]=YELLOW;
            }
            else {
                if (tablero[x][j].Color!=tablero[x][y].Color) {
                    color_tablero[x][j]=RED;
                }
                break;
            }
        }
    }

    if (tablero[x][y].Pieza==REINA || tablero[x][y].Pieza==ALFIL) {
        for (int i=x+1,j=y+1;i<8 && j<8;i++,j++) {
            if (tablero[i][j].Pieza==VACIO) {
                color_tablero[i][j]=YELLOW;
            }
            else {
                if (tablero[i][j].Color!=tablero[x][y].Color) {
                    color_tablero[i][j]=RED;
                }
                break;
            }
        }

        for (int i=x+1,j=y-1;i<8 && j>=0;i++,j--) {
            if (tablero[i][j].Pieza==VACIO) {
                color_tablero[i][j]=YELLOW;
            }
            else {
                if (tablero[i][j].Color!=tablero[x][y].Color) {
                    color_tablero[i][j]=RED;
                }
                break;
            }
        }

        for (int i=x-1,j=y+1;i>=0 && j<8;i--,j++) {
            if (tablero[i][j].Pieza==VACIO) {
                color_tablero[i][j]=YELLOW;
            }
            else {
                if (tablero[i][j].Color!=tablero[x][y].Color) {
                    color_tablero[i][j]=RED;
                }
                break;
            }
        }

        for (int i=x-1,j=y-1;i>=0 && j>=0;i--,j--) {
            if (tablero[i][j].Pieza==VACIO) {
                color_tablero[i][j]=YELLOW;
            }
            else {
                if (tablero[i][j].Color!=tablero[x][y].Color) {
                    color_tablero[i][j]=RED;
                }
                break;
            }
        }
    }

    if (tablero[x][y].Pieza==REY) {
        //cout << "Se selecciono el REY\n";
        int mov_i[8]={0,1,1,1,0,-1,-1,-1};
        int mov_j[8]={1,1,0,-1,-1,-1,0,1};
        //cout << "-----------------------\n";
        tablero[x][y].Pieza=VACIO;
        for (int i=0;i<8;i++) {
            int k,h;
            //cout << x << " " << y << "->";
            k=x+mov_i[i];
            h=y+mov_j[i];
            if (k<8 && k>=0 && h<8 && h>=0) {
                if (!checaMate(tablero,tablero[x][y].Color,k,h)) {
                    //cout << k <<  " " << h << "\n";
                    if (tablero[k][h].Pieza!=VACIO && tablero[k][h].Color!=tablero[x][y].Color){
                        color_tablero[k][h]=RED;
                    }
                    else {
                        if (tablero[k][h].Pieza==VACIO){
                            color_tablero[k][h]=YELLOW;
                        }
                    }
                }
            }
        }
        int k,h;
        for (k=y+1;k<8 && tablero[x][k].Pieza==VACIO;k++){}
        for (h=y-1;h>=0 && tablero[x][h].Pieza==VACIO;h--){}

        if (k==7 && enro_der && !checaMate(tablero,tablero[x][y].Color,7,6)) {
            color_tablero[7][6]=YELLOW;
        }

        if (h==0 && enro_izq && !checaMate(tablero,tablero[x][y].Color,7,1)) {
            color_tablero[7][1]=YELLOW;
        }

        tablero[x][y].Pieza=REY;
    }
}

bool Movimiento_Valido (int I, int J) {
    if (color_tablero[I][J]==YELLOW || color_tablero[I][J]==RED){
        return true;
    }
    return false;
}

bool danger (pieza **tablero,bool col) {
    //cout << "ENTRA";
    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++) {
            if (tablero[i][j].Pieza==REY && tablero[i][j].Color==col) {
                //cout << i << " " << j << "\n";
                return checaMate(tablero,col,i,j);
            }
        }
    }
}

void Accion(pieza **tablero, bool PlayColor, int deep, bool solo_check){
    if (deep==1) {
        //imprime_tablero();
    }

    if (deep==1 && danger(tablero,!PlayColor)) {
            cont_check++;delay(100);
            return;
    }
    if (deep==1 && solo_check) {
        return;
    }

    if(deep == 4){
        int t = peso(tablero,PlayColor);
        if(t>best_future || (t == best_future && rand()%5==0)){
            best_future=t;
            awake=true;
        }
        return ;
    }
    for(int i=0 ; i<8 ; i++){
        for(int j=0 ; j<8 ; j++){
            if(VACIO != tablero[i][j].Pieza && PlayColor == tablero[i][j].Color){
                Colorear_Casillas(tablero,color_tablero,i,j);
                for(int k=0 ; k<8 ; k++){
                    for(int l=0 ; l<8 ; l++){
                        if(Movimiento_Valido(k,l)){
                            if (deep==0) {
                                cont_val++;
                            }
                            pieza axis_in, axis_out;        /*  Auxiliares */
                            axis_in.Color = tablero[i][j].Color;
                            axis_in.Pieza = tablero[i][j].Pieza;
                            axis_out.Color = tablero[k][l].Color;
                            axis_out.Pieza = tablero[k][l].Pieza;
                            tablero[k][l].Color = axis_in.Color;
                            tablero[k][l].Pieza = axis_in.Pieza;
                            tablero[i][j].Pieza = VACIO;
                            if (tablero[k][l].Pieza==PEON_N) {
                                tablero[k][l].Pieza=PEON_N;
                            }
//                            imprime_tablero();
//                            cout << k << " " << l << "\n";
                            //system("pause");
                            Tablero_Color_rst(tablero,color_tablero);
                            Accion(tablero,!PlayColor,deep+1,solo_check);
                            if(deep==0 && awake){
                                //t_best=tablero;
                                copea();
                                //imprime_t();
                                //imprime_tablero();
                                //cout << "ax" << endl;
                                awake=false;
                            }
                            Tablero_Color_rst(tablero,color_tablero);
                            tablero[k][l].Color = axis_out.Color;
                            tablero[k][l].Pieza = axis_out.Pieza;
                            tablero[i][j].Color = axis_in.Color;
                            tablero[i][j].Pieza = axis_in.Pieza;
                            Colorear_Casillas(tablero,color_tablero,i,j);
                        }
                    }
                }
                Tablero_Color_rst(tablero,color_tablero);
            }
        }
    }
}

Tipo crown () {
    settextstyle(0,HORIZ_DIR,3);
    outtextxy(680,35,"¿Que pieza escoges?");
    Draw_Quen(40,680,WHITE);
    Draw_Bishop(120,680,WHITE);
    Draw_Knight(200,680,WHITE);
    Draw_Rock(280,680,WHITE);
    int _x,_y;
    Tipo regresa;
    while ((_x<=760 || _x>=680) && (_y<=360 || _y>=40)) {
        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        getmouseclick(WM_LBUTTONDOWN,_x,_y);
        //cout << _x << " " << _y << "\n";
        clearmouseclick(WM_LBUTTONDOWN);
        if (((_x<=760 || _x>=680) && (_y<=360 || _y>=40))) {
            break;
        }
    }
    if (_y<120) {
        regresa=REINA;
    }
    else if (_y<200) {
        regresa=ALFIL;
    }
    else if (_y<280) {
        regresa=CABALLO;
    }
    else {
        regresa=TORRE;
    }

    return regresa;
}

void Game (pieza **tablero) {
    int playNumber=0;
    bool MvValid=false;
    bool check1;
    bool check2;
    while (1) {
        int x,y;
        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        getmouseclick(WM_LBUTTONDOWN,x,y);
        int i,j;
        j=(x-30)/80;
        i=(y-30)/80;
        if (tablero[i][j].Pieza!=VACIO && !tablero[i][j].Color) {
            Colorear_Casillas(tablero,color_tablero,i,j);
            Draw_Game(tablero);
            while (!ismouseclick(WM_LBUTTONDOWN)) {}
            getmouseclick(WM_LBUTTONDOWN,x,y);
            int _i,_j;
            _j=(x-30)/80;
            _i=(y-30)/80;
            if (Movimiento_Valido(_i,_j)) {

                if (tablero[i][j].Pieza==REY && _i==7 && _j==6 && enro_der) {
                    tablero[7][5]=tablero[7][7];
                    tablero[7][7].Pieza=VACIO;
                    enro_der=false;
                }
                if (tablero[i][j].Pieza==REY && _i==7 && _j==1 && enro_izq) {
                    tablero[7][2]=tablero[7][0];
                    tablero[7][0].Pieza=VACIO;
                    enro_izq=false;
                }
                if (tablero[i][j].Pieza==TORRE && i==7 && j==7) {
                    enro_der=false;
                }
                if (tablero[i][j].Pieza==TORRE && i==7 && j==0) {
                    enro_izq=false;
                }
                if (tablero[i][j].Pieza==REY && (abs(i-_i)<=1 || abs(j-_j)<=1)) {
                    enro_der=enro_izq=false;
                }

                tablero[_i][_j]=tablero[i][j];
                if (tablero[_i][_j].Pieza==PEON_N) {
                    tablero[_i][_j].Pieza=PEON_U;
                }
                if (tablero[_i][_j].Pieza==PEON_U && _i==0) {
                    tablero[_i][_j].Pieza=crown();
                }
                tablero[i][j].Pieza=VACIO;
                MvValid=true;
                if (danger(tablero,false)) {
                    MvValid=false;
                    tablero[i][j]=tablero[_i][_j];
                    tablero[_i][_j].Pieza=VACIO;
                }
                cont_check=0;
                cont_val=0;
                Accion(tablero,true,0,true);
                if (cont_check==cont_val) {
                    Tablero_Color_rst(tablero,color_tablero);
                    Draw_Game(tablero);
                    delay(400);
                    settextstyle(0,HORIZ_DIR,5);
                    outtextxy(50,300,"FELICIDADES GANASTE");
                    delay(500);
                    getch();
                    exit(0);
                }
            }
            Tablero_Color_rst(tablero,color_tablero);
            Draw_Game(tablero);
            if (danger(tablero,true)) {
                settextstyle(0,HORIZ_DIR,4);
                outtextxy(680,40,"CHECK!");
            }
            if(MvValid==true){
                if(playNumber<6){
                    delay(500);
                    if(tablero[desde[rnd][playNumber][0]][desde[rnd][playNumber][1]].Pieza!=VACIO && !danger(tablero,true)){
                        tablero[hasta[rnd][playNumber][0]][hasta[rnd][playNumber][1]].Pieza = tablero[desde[rnd][playNumber][0]][desde[rnd][playNumber][1]].Pieza;
                        tablero[hasta[rnd][playNumber][0]][hasta[rnd][playNumber][1]].Color = tablero[desde[rnd][playNumber][0]][desde[rnd][playNumber][1]].Color;
                        tablero[desde[rnd][playNumber][0]][desde[rnd][playNumber][1]].Pieza=VACIO;
                        if (tablero[hasta[rnd][playNumber][0]][hasta[rnd][playNumber][1]].Pieza==PEON_N) {
                            tablero[hasta[rnd][playNumber][0]][hasta[rnd][playNumber][1]].Pieza=PEON_U;
                        }
                        if (danger(tablero,true)) {
                            tablero[desde[rnd][playNumber][0]][desde[rnd][playNumber][1]]=tablero[hasta[rnd][playNumber][0]][hasta[rnd][playNumber][1]];
                            best_future=0;
                            Accion(tablero,true,0,false);
                            copea2();
                            playNumber=6;
                        }
                        playNumber++;
                    }
                    else {
                        best_future=0;
                        Accion(tablero,true,0,false);
                        copea2();
                        playNumber=6;
                    }
                }
                else {
                    best_future=0;
                    Accion(tablero,true,0,false);
                    copea2();
                    //imprime_t();
                    //imprime_tablero();
                    //cout << 2<< endl;
                }
                MvValid=false;
                cont_check=0;
                cont_val=0;
                Accion(tablero,false,0,true);
                if (cont_check==cont_val) {
                    Tablero_Color_rst(tablero,color_tablero);
                    Draw_Game(tablero);
                    delay(400);
                    settextstyle(0,HORIZ_DIR,10);
                    outtextxy(50,50,"LO SENTIMOS PERDISTE");
                    delay(500);
                    getch();
                }
            }
            Draw_Game(tablero);
            if (danger(tablero,false)) {
                settextstyle(0,HORIZ_DIR,4);
                outtextxy(680,40,"CHECK!");
            }
        }
    }
}

int main(){
    //pieza **tablero= new pieza* [8];
    srand(time(NULL));
    for (int i=0;i<8;i++) {
        tablero[i]=new pieza[8];
        t_best[i]=new pieza[8];
        color_tablero[i]=new int[8];
    }
    srand (time(NULL));
    rnd=rand()%5;
    //rnd=0;
    //cout << rnd << "<-\n";
    inicio();
    imprime_tablero();
    initwindow(1000,700);
    GLOBAL_COLOR=DARKGRAY;
    setcolor(GLOBAL_COLOR);
    PLAYER1=CYAN;
    PLAYER2=RED;
    Tablero_Color_rst(tablero,color_tablero);
    Draw_Game(tablero);
    Game(tablero);
    cin.get();
    return 0;
}
