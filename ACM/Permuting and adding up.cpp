#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

int main () {

    long long factorial[20];
    factorial[0]=1;
    factorial[1]=1;
    factorial[2]=2;
    factorial[3]=6;
    factorial[4]=24;
    factorial[5]=120;
    factorial[6]=720;
    factorial[7]=5040;
    factorial[8]=40320;
    factorial[9]=362880;
    factorial[10]=3628800;
    factorial[11]=39916800;
    factorial[12]=479001600;

    int T;
    scanf("%d",&T);
    while (T--) {
        char N[20];
        scanf("%s",N);

        long long n=strlen(N);
        long long unos=0;

        long long repeticiones[15];
        for (int i=0;i<15;i++) {
            repeticiones[i]=0;
        }

        for (int i=0;i<n;i++) {
            unos*=10;
            unos++;
            repeticiones[N[i]-'0']++;
        }

        long long numerador=factorial[n];
        long long denominador=1;
        for (int i=0;i<15;i++) {
            denominador*=factorial[repeticiones[i]];
        }

        long long ans=0;
        long long K;

        //cout << numerador << " " << denominador << "\n";

        for (int i=0;i<10;i++) {
            if (repeticiones[i]>0) {
                int M=repeticiones[i];
                if (M<=0){
                    M=1;
                }
                K=(numerador/n)/(denominador/(M));
                ans+=K*unos*(i);
            }
        }
//        if (numerador/denominador==1){
//            cout << 1 << " " << N << "\n";
//            continue;
//        }

        cout << numerador/denominador << " " << ans << "\n";
    }
    return 0;
}
