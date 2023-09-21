/*
 * Author: arefa29
 * Date: Wed Nov 16 2022
 */

#include<bits/stdc++.h>
using namespace std;

char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int mark[26] = {0};
int matrix[5][5];
int row[26] = {0};
int col[26] = {0};

int mark2[26] = {0};
int matrix2[5][5];
int row2[26] = {0};
int col2[26] = {0};

// creating the 5x5 matrix using key
class PlayfairMatrix{
    public:
        PlayfairMatrix(string key){
            int k =  0, i, j;
            int len = key.length();
            // fill key into matrix
            for(i = 0; i < 5; i++){
                for(j = 0; j < 5 && k < key.length(); j++){
                    matrix[i][j] = key[k] - 'a';
                    mark[key[k] - 'a'] = 1;
                    row[key[k] - 'a'] = i;
                    col[key[k] - 'a'] = j;
                    k++;
                }
            }
            // fill row remaining elements
            k  = 0;
            for(i = len / 5; i <= len / 5; i++){
                for(j = len % 5; j < 5; j++){
                    while(mark[k] == 1){
                        k++;
                    }
                    matrix[i][j] = k;
                    mark[k] = 1;
                    row[k] = i;
                    col[k] = j;
                    if(matrix[i][j] == 8){ // if it is i
                        if(mark[k+1] == 0){ // and j hasn't already been marked, skip j
                            k++;
                        }
                    }
                    k++;
                }
            }
            // fill the remaining rows
            k = 0;
            for(; i < 5; i++){
                for(j = 0; j < 5; j++){

                    while(mark[k] == 1){
                        k++;
                    }
                    matrix[i][j] = k;
                    mark[k] = 1;
                    row[k] = i;
                    col[k] = j;
                    if(matrix[i][j] == 8){
                        if(mark[k+1] == 0){
                            k++;
                        }
                    }
                    k++;
                }
            }

            cout << "\n-----------Matrix-------------\n";
            for(i = 0; i < 5; i++){
                for(j = 0; j < 5; j++){
                    cout << letters[matrix[i][j]] << " ";
                }
                cout << endl;
            }
            cout << "-------------------------------\n";
        }      

        PlayfairMatrix(string key, int flag){
            int k =  0, i, j;
            int len = key.length();
            // fill key into matrix
            for(i = 0; i < 5; i++){
                for(j = 0; j < 5 && k < key.length(); j++){
                    matrix2[i][j] = key[k] - 'a';
                    mark2[key[k] - 'a'] = 1;
                    row2[key[k] - 'a'] = i;
                    col2[key[k] - 'a'] = j;
                    k++;
                }
            }
            // fill row remaining elements
            k  = 0;
            for(i = len / 5; i <= len / 5; i++){
                for(j = len % 5; j < 5; j++){
                    while(mark2[k] == 1){
                        k++;
                    }
                    matrix2[i][j] = k;
                    mark2[k] = 1;
                    row2[k] = i;
                    col2[k] = j;
                    if(matrix2[i][j] == 8){ // if it is i
                        if(mark2[k+1] == 0){ // and j hasn't already been mark2ed, skip j
                            k++;
                        }
                    }
                    k++;
                }
            }
            // fill the remaining rows
            k = 0;
            for(; i < 5; i++){
                for(j = 0; j < 5; j++){

                    while(mark2[k] == 1){
                        k++;
                    }
                    matrix2[i][j] = k;
                    mark2[k] = 1;
                    row2[k] = i;
                    col2[k] = j;
                    if(matrix2[i][j] == 8){
                        if(mark2[k+1] == 0){
                            k++;
                        }
                    }
                    k++;
                }
            }

            cout << "\n-----------Matrix-------------\n";
            for(i = 0; i < 5; i++){
                for(j = 0; j < 5; j++){
                    cout << letters[matrix2[i][j]] << " ";
                }
                cout << endl;
            }
            cout << "-------------------------------\n";
        }
};

string findCipher(string group){
    string cipher(2, 0);
    int row1 = row[group[0] - 'a'];
    int col1 = col[group[0] - 'a'];
    int row2 = row[group[1] - 'a'];
    int col2 = col[group[1] - 'a'];

    if(row1 == row2 && col1 != col2){
        cipher[0] = letters[matrix[row1][(col1 + 1)%5]];
        cipher[1] = letters[matrix[row1][(col2 + 1)%5]];
    }
    else if (row1 != row2 && col1 == col2){
        cipher[0] = letters[matrix[(row1+1) % 5][col1]];
        cipher[1] = letters[matrix[(row2+1) % 5][col1]];
    }
    else {
        cipher[0] = letters[matrix[row1][col2]];
        cipher[1] = letters[matrix[row2][col1]];
    }
    cout << "cipher = " << cipher << endl;
    return cipher;
}

string playfairEncrypt(string plain_text){
    string group(2, 0);
    string cipher_text;
    int i,j;

    for(i = 0; i < plain_text.length(); i += 2){
        j = i+1;
        group[0] = plain_text[i];
        if(j == plain_text.length()){
            group[1] = 'z';
        }
        else if(plain_text[j] != plain_text[i]){
            group[1] = plain_text[j];
        }
        else if(plain_text[j] == plain_text[i]){
            i--;
            group[1] = 'x';
        }
        if(group[0] == 'j'){
            group[0] == 'i';
        }
        if (group[1] == 'j'){
            group[1] == 'i';
        }
        cout << "group = " << group << " | ";
        cipher_text.append(findCipher(group));
    }
    return cipher_text;
}

int mod5(int a){
    if (a < 0)
        a += 5;
    return (a % 5);
}

string findCipherReverse(string group){
    string cipher(2, 0);
    int row0 = row2[group[0] - 'a'];
    int col0 = col2[group[0] - 'a'];
    int row10 = row2[group[1] - 'a'];
    int col10 = col2[group[1] - 'a'];

    if(row0 == row10 && col0 != col10){
        cipher[0] = letters[matrix2[row0][mod5(col0 - 1)]];
        cipher[1] = letters[matrix2[row0][mod5(col10 - 1)]];
    }
    else if (row0 != row10 && col0 == col10){
        cipher[0] = letters[matrix2[mod5(row0 - 1)][col0]];
        cipher[1] = letters[matrix2[mod5(row10 - 1)][col0]];
    }
    else {
        cipher[0] = letters[matrix2[row0][col10]];
        cipher[1] = letters[matrix2[row10][col0]];
    }
    cout << "cipher = " << cipher << endl;
    return cipher;
}

string playfairDecrypt(string cipher_text){
    string plain_text;
    string group(2,0);
    int i, j;
    // always even
    for(i = 0; i<cipher_text.length(); i+=2){
        j = i + 1;
        group[0] = cipher_text[i];
        group[1] = cipher_text[j];
        cout << "group = " << group << " | ";
        plain_text.append(findCipherReverse(group));
    }

    return plain_text;
}

// Convert the string to lowercase
void toLowerCase(string &str){
    int i;
    for (i = 0; i < str.length(); i++) {
        if (str[i] > 64 && str[i] < 91)
            str[i] += 32;
    }
}
 
// Remove all spaces in a string
string removeSpaces(string str){
    int i;
    string res;
    for (i = 0; i < str.length(); i++){
        if (str[i] != ' '){
            res.push_back(str[i]);
        }
    }
    return res;
}

int main(){
    int choice;
    string plain_text, key, cipher_text, decrypted;

    while(1){
        cout << "\n--------------------------------OPTIONS--------------------------------\n";
        cout << "1. Encrypt using Playfair Cipher\n";
        cout << "2. Exit\n";
        cout << "3. Decrypt\n";
        cout << "Choice: "; cin >> choice;
        cout << "-----------------------------------------------------------------------\n";

        switch(choice){
            case 1:
            {
                cout << "\nEnter input message: ";
                fflush(stdin);
                getline(cin, plain_text);
                cout << "Enter key: ";
                cin >> key;

                PlayfairMatrix obj(key);
                toLowerCase(plain_text);
                plain_text = removeSpaces(plain_text);

                cipher_text = playfairEncrypt(plain_text);

                cout << "\n-----------------------------------------------------------------------\n";
                cout << "Cipher text: " << cipher_text << endl;
                cout << "-----------------------------------------------------------------------\n";
                break;
            }

            case 2:
                exit(0);

            case 3:
            {
                cout << "Enter key: ";
                cin >> key;

                PlayfairMatrix obj2(key, 0); // make a new matrix acc to this key

                plain_text = playfairDecrypt(cipher_text);
                cout << "\n-----------------------------------------------------------------------\n";
                cout << "Plain text: " << plain_text << endl;
                cout << "-----------------------------------------------------------------------\n";
                break;
            }

            default:
                cout << "\nWrong input. Enter 1 or 2.\n";
        }
    }

    return 0;
}