#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector < vector <int > > vec;

int main () {
    string S;
    cin >> S;

    vec.resize(300);

    for (int i=0;i<S.size();i++) {
        int tmp=int(S[i]);
        vec[tmp].push_back(i);
    }

    int T;
    scanf("%d",&T);

    while (T--) {
        char K;
        int a,b;
        cin >> K;
        int aux=int(K);
        scanf("%d%d",&a,&b);
        int jalo=false;
        int ini=0;
        int fin=vec[aux].size()-1;

        if (vec[aux].size()==0) {
            printf("0\n");
            continue;
        }

        while (ini+1<fin) {
            int med=(ini+fin)/2;
            if (vec[aux][med]<=a) {
                ini=med;
            }
            else {
                fin=med;
            }
        }

        if (vec[aux][ini]>=a && vec[aux][ini]<=b+a-1)
            jalo=true;

        if (vec[aux][fin]>=a && vec[aux][fin]<=b+a-1)
            jalo=true;


        if (jalo) {
            printf("1\n");
        }
        else {
            printf("0\n");
        }
    }

    return 0;
}
