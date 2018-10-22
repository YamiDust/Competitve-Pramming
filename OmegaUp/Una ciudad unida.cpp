#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

pair < int , int > subset[2010];

int Find (int x) {
    if (subset[x].first!=x)
        subset[x].first=Find(subset[x].first);

    return subset[x].first;
}

int memo[2010];

void Union (int a,int b) {
    int aroot=Find(a);
    int broot=Find(b);

    if (subset[aroot].second < subset[broot].second) {
        subset[aroot].first=broot;
    }
    else if (subset[aroot].second > subset[broot].second) {
        subset[broot].first=aroot;
    }
    else {
        subset[broot].first=aroot;
        subset[aroot].second++;
    }
}

int main () {

    int N,T;
    scanf("%d%d",&N,&T);

    for (int i=1;i<=N;i++) {
        subset[i].first=i;
    }

    while (T--) {
        int a,b;
        scanf("%d%d",&a,&b);
        Union(a,b);
    }


    for (int i=1;i<=N;i++) {
        memo[Find(i)]++;
    }

    int cont=0;
    for (int i=1;i<=N;i++) {
        for (int j=i+1;j<=N;j++) {
            cont+=(memo[i]*memo[j]);
        }
    }

    printf("%d",cont);

    return 0;
}
