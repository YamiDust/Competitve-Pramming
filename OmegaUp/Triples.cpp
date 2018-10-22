#include <stdio.h>
#include <iostream>

using namespace std;

long long arr[50100];

int main () {

    int N;
    scanf("%d",&N);
    int cont=0;

    for (int i=0;i<N;i++) {
        scanf("%lld",&arr[i]);
        if (arr[i]%3==0)
            cont++;
    }

    if (cont==0) {
        printf("No hay triples.");
        return 0;
    }

    printf("%d\n",cont);

    for (int i=0;i<N;i++) {
        if (arr[i]%3==0)
            printf("%d ",i+1);
    }

    return 0;
}

