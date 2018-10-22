#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int mat[500][1000010];

int main () {
    string S;

    cin >> S;

    vector <vector <int > > vec;
    vec.resize(600);
    for (int i=0;i<S.size();i++) {
        int tmp=int(S[i])+256;
        vec[tmp].push_back(i);
    }

    int T;
    scanf("%d",&T);

    while (T--) {
        char K;
        int a,b;
        cin >> K;
        int aux=int(K)+256;
        scanf("%d%d",&a,&b);
        int jalo=false;
        for (int i=0;i<vec[aux].size();i++) {
            if (vec[aux][i]>=a && vec[aux][i]<=b) {
                jalo=true;
                break;
            }
        }
        if (jalo) {
            printf("1\n");
        }
        else {
            printf("0\n");
        }
    }

    return 0;
}
