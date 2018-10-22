#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int bucket[50];
int costo[50];

int main () {

    int N;
    scanf("%d",&N);

    string S,T;
    cin.ignore();
    getline(cin,S);
    scanf("%d",&N);
    cin.ignore();
    getline(cin,T);

    for (int i=0;i<26;i++) {
        scanf("%d",&costo[i]);
    }

    for (int i=0;i<T.size();i+=2) {
        bucket[T[i]-'A']++;
    }

    int cont=0;
    for (int i=0;i<S.size();i+=2) {
        if (bucket[S[i]-'A']>0) {
            cont+=costo[S[i]-'A'];
            bucket[S[i]-'A']--;
        }
    }

    printf("%d\n",cont);

    return 0;
}
