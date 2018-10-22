#include <stdio.h>
#include <iostream>

using namespace std;

struct Data {
    int P,Q;
};

Data arr[10010];

int particion (int izq, int der) {
    int pivot,i,j;
    i=izq-1;
    pivot=arr[der].P;
    for (int j=izq;j<=der-1;j++) {
        if (arr[j].P<=pivot) {
            i++;
            Data tmp=arr[i];
            arr[i]=arr[j];
            arr[j]=tmp;
        }
    }
    i++;
    Data tmp=arr[i];
    arr[i]=arr[der];
    arr[der]=tmp;
    return i;
}

void quicksort (int izq, int der) {
    int pi;
    if (izq < der) {
        pi=particion (izq,der);
        quicksort(izq,pi-1);
        quicksort(pi+1,der);
    }
}


int main () {
    int I,N;
    scanf("%d%d",&I,&N);

    for (int i=0;i<N;i++) {
        scanf("%d%d",&arr[i].P,&arr[i].Q);
    }

    quicksort(0,N-1);

    for (int i=0;i<N;i++) {
        if (I>arr[i].P) {
            I+=arr[i].Q;
        }
        else {
            printf("NO");
            return 0;
        }
    }

    printf("SI");

    return 0;
}
