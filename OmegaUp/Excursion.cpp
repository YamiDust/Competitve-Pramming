#include <stdio.h>
#include <iostream>

using namespace std;

int arr[10100];

int main () {

    int N,P;
    scanf("%d%d",&N,&P);

    for (int i=0;i<N;i++) {
        scanf("%d",&arr[i]);
    }

    while (P--) {
        int tmp;
        scanf("%d",&tmp);
        printf("%d\n",arr[tmp-1]);
    }

    return 0;
}
