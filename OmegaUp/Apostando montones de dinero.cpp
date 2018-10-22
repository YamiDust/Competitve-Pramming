#include <stdio.h>
#include <iostream>
#include <math.h>
#include <limits.h>

using namespace std;

int K[1010];
int A[1010];

int main () {
    int N;
    scanf("%d",&N);

    for (int i=0;i<N;i++) {
        scanf("%d",&K[i]);
    }

    for (int i=0;i<N;i++) {
        scanf("%d",&A[i]);
    }

    for (int i=0;i<N;i++) {
        for (int j=i;j>0 && K[j]>K[j-1];j--) {
            int tmp=K[j];
            K[j]=K[j-1];
            K[j-1]=tmp;
        }
    }

    for (int i=0;i<N;i++) {
        for (int j=i;j>0 && A[j]>A[j-1];j--) {
            int tmp=A[j];
            A[j]=A[j-1];
            A[j-1]=tmp;
        }
    }

    int pos=0;
    int ans=0;
    for (int i=0;i<N;i++) {
        if (K[i]<A[pos]) {
            ans+=A[pos++];
        }
    }

    printf("%d",ans);

    return 0;
}
