#include <bits/stdc++.h>
#include <graphics.h>


using namespace std;

enum Tipo {PEON_N, PEON_U, CABALLO, REINA, REY, TORRE, VACIO,ALFIL};

struct pieza {
  Tipo Pieza;
  bool Color;
};
int GLOBAL_COLOR,PLAYER1,PLAYER2;
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
    void Draw_Board(){
        int cont=0;
        rectangle(30,30,670,670);
        for(int i=30;i<670;i+=80){
            for(int j=30;j<670;j+=80){
                cont++;
                if(cont%2==0){
                    int *ax = new int[8];
                    ax[0]=j;
                    ax[1]=i;
                    ax[2]=j+80;
                    ax[3]=i;
                    ax[4]=j+80;
                    ax[5]=i+80;
                    ax[6]=j;
                    ax[7]=i+80;
                    fillpoly(4,ax);
                }
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
        Draw_Board();
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
    }
int main(){
    //pieza **tablero= new pieza* [8];

    for (int i=0;i<8;i++) {
        tablero[i]=new pieza[8];
    }
    inicio();
    imprime_tablero();
    initwindow(1000,700);
    GLOBAL_COLOR=DARKGRAY;
    setcolor(GLOBAL_COLOR);
    PLAYER1=CYAN;
    PLAYER2=RED;
    Draw_Game(tablero);
    cin.get();
    return 0;
}
