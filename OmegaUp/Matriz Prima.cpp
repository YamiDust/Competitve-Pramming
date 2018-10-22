#include <stdio.h>
#include <iostream>
#include <math.h>
#include <limits.h>

using namespace std;

int primos[100100];

int esPrimo (int x) {
    int raiz=sqrt(x);
    for (int i=2;i<=raiz;i++) {
        if (x%i==0)
            return 0;
    }
    return 1;
}

int mat[510][510];
int marca[510][510];

int main () {
    int N,M;

    scanf("%d%d",&N,&M);
    for (int i=0;i<N;i++) {
        for (int j=0;j<M;j++) {
            scanf("%d",&mat[i][j]);
        }
    }

    for (int i=2;i<=100100;i++) {
        primos[i]=esPrimo(i);
    }

    for (int i=100100-1;i>0;i--) {
        if (!primos[i]) {
            primos[i]=primos[i+1]+1;
        }
    }

    //cout << primos[100000] << "\n";

    for (int i=0;i<N;i++) {
        for (int j=0;j<M;j++) {
            marca[i][j]=primos[mat[i][j]]-1;
            //cout << marca[i][j] << " ";
        }
        //cout << endl;
    }

    int ans=INT_MAX;
    int cont;

    for (int i=0;i<N;i++) {
        cont=0;
        for (int j=0;j<M;j++) {
            cont+=marca[i][j];
        }
        ans=min(ans,cont);
    }

    for (int i=0;i<M;i++) {
        cont=0;
        for (int j=0;j<N;j++) {
            cont+=marca[j][i];
        }
        ans=min(ans,cont);
    }

    printf("%d",ans);

    return 0;
}
