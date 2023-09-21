#include <bits/stdc++.h>
using namespace std;

vector<char> encryptString(vector<char> plainText, int key){

    int noOfSymbol = plainText.size();
    int noOfRows = noOfSymbol / key + ((noOfSymbol % key) ? 1 : 0);

    vector<vector<char> > encryptedMatrix(noOfRows, vector<char>(key, 'a'));
    vector<char> encrypted;

    int k=0;
    int i,j;
    for(i=0; i<noOfRows; i++){
        for(j=0; j<key; j++){
            if(k != plainText.size()){
                encryptedMatrix[i][j] = plainText[k];
                k++;
            }
            else {
                break; // this only breaks out of the first loop, leading to last i++
            }
        }
    }

    // filling remaining
    if(j != key){
        i--; // go back to last row
        for(; j<key; j++){
           encryptedMatrix[i][j] = 'x';
        }
    }

    // reading matrix columnwise
    for(i=0; i<key; i++){
        for(j=0; j<noOfRows; j++){
            encrypted.push_back(encryptedMatrix[j][i]);
        }
    }
    
    return encrypted;
}

vector<char> decryptString(vector<char> cipherText, int key){

    int totalLength = cipherText.size();
    int noOfRows = totalLength / key;

    vector<char> decryptedString;

    for(int i=0; i<noOfRows; i++){
        for(int k=0; k<key; k++){

            int idx = i + k*noOfRows;
            if(idx > totalLength){
                continue;
            }
            if(cipherText[idx] == 'x'){
                continue;
            }
            decryptedString.push_back(cipherText[idx]);
        }
    }

    return decryptedString;
}

int main(){
    int choice;
    vector<char> input;
    string inputstr;
    int key;
    vector<char> encrypted;
    vector<char> decrypted;    

    while(1){
        cout << "\n----------TRANSPOSITION CIPHER-----------" <<endl;
        cout << "1. Encrypt string" << endl;
        cout << "2. Decrypt string" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;
        cout << "------------------------------------------" <<endl;

        switch(choice){
            case 1: 
                cout << "Enter input message: " << endl;
                fflush(stdin);
                getline(cin, inputstr);

                input.clear();
                for(auto s: inputstr){
                    if(s != ' ')
                        input.push_back((char)s);
                }

                cout << "Enter key: ";
                cin >> key;

                encrypted = encryptString(input, key);
                cout << "--------------------------------------------" << endl;
                cout << "Encrypted string = ";
                for(int i=0; i<encrypted.size(); i++){
                    cout << encrypted[i] << " ";
                }
                cout << "\n--------------------------------------------\n";
                break;

            case 2:
                cout << "Enter key: ";
                cin >> key;

                decrypted = decryptString(encrypted, key);
                cout << "\n--------------------------------------------\n";
                cout << "Decrypted string = ";
                for(auto c : decrypted){
                    cout << c << " ";
                }
                cout << "\n--------------------------------------------\n";
                break;
            
            case 3:
                exit(0);

            default: cout << "Wrong choice\n";
        }
    }
    return 0;
}