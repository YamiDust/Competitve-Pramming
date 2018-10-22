#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int mat[110][110];

pair <int, int > arr[10100];

int main () {

    int N,M;
    scanf("%d%d",&N,&M);

    for (int i=0;i<N;i++) {
        for (int j=0;j<M;j++) {
            int tmp;
            scanf("%d",&tmp);
            arr[tmp].first=i;
            arr[tmp].second=j;
        }
    }

    int ans=0;
    int cont=1;
    for (int i=0;i<10100;i++) {
        //cout << i << " " << (abs(arr[i].first-arr[i+1].first)+abs(arr[i].second-arr[i+1].second)) << "\n";
        if ((abs(arr[i].first-arr[i+1].first)+abs(arr[i].second-arr[i+1].second))==1) {
            cont++;
        }
        else {
            ans=max(cont,ans);
            cont=1;
        }
    }
    ans=max(ans,cont);


    printf("%d\n",ans);

    return 0;
}
