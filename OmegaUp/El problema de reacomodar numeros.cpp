#include <stdio.h>
#include <math.h>
#include <iostream>


using namespace std;


int main () {

    int N;
    scanf("%d",&N);

    long long ans=1;

    for (int i=0;i<N-1;i++) {
        ans*=2;
    }

    printf("%lld",ans);

    return 0;

}
