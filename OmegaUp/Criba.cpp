#include <stdio.h>
#include <iostream>

using namespace std;

bool primos[1000010];

void criba () {
    primos[0]=primos[1]=true;
    for (long long i=4;i<=1000000;i+=2) {
        primos[i]=true;
    }
    for (long long i=3;i<=1000000;i+=2) {
        if (!primos[i]) {
            for (long long j=i*i;j<=1000000;j+=i) {
                primos[j]=true;
            }
        }
    }
}

int main () {

    int T;
    scanf("%d",&T);
    criba();
    while (T--) {
        int tmp;
        scanf("%d",&tmp);
        if (primos[tmp])
            puts("NO");
        else
            puts("SI");
    }

    return 0;
}

