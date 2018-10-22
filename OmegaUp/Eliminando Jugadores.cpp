#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

bool memo[1010];

int main () {

    int N,K;
    scanf("%d%d",&N,&K);

    int pasos=2;
    int cont=N-2;
    int i=3;
    while (cont>1) {
        int j=1;
        while (j<pasos) {
            if (!memo[i]) {
                j++;
            }
            i++;
            if (i>N) {
                i=3;
            }
        }
        while (memo[i])
        {
            i++;
            if (i>N) {
                i=3;
            }
        }
        memo[i]=true;
        cont--;
        pasos++;
    }



    for (int j=3;j<=N;j++) {
        if (!memo[j]) {
            int tmp=K-(j-1);
            if (tmp<=0) {
                tmp+=N;
            }
            printf("%d",tmp);
            return 0;
        }
    }

    return 0;

}
