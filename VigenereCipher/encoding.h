#include<bits/stdc++.h>
using namespace std;

char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int matrix[26][26];

class Matrix {
    public:
        Matrix(){
            for(int i=1; i <= 26; i++){
                for(int j=1; j <= 26; j++){
                    if((j + (i-1)) == 26){
                        matrix[i-1][j-1] = (j + (i-1));
                        continue;
                    }
                    matrix[i-1][j-1] = (j + (i-1))%26;
                }
            }
        }
};
