#include <stdio.h>
#include <iostream>

using namespace std;

int main () {

    long long N;
    scanf("%lld",&N);

    int cont=0;

    while ((N-1)%11>0) {
        N*=2;
        cont++;
    }

    printf("%d %lld",cont,N);

    return 0;
}
