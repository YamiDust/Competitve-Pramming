#include <stdio.h>
#include <iostream>

using namespace std;

int main () {

    long long N,M;
    scanf("%lld%lld",&N,&M);

    printf("%lld ",(N/M));
    if (N%M>0) {
        printf("%lld/%lld",(N%M),M);
    }

    return 0;
}

