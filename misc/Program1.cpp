#include<bits/stdc++.h>
using namespace std;

vector<char> lower;
vector<char> upper;

vector<char> encryptString(vector<char> s, int key){
    vector<char> encrypted;
    int idx;
    
    for(auto c : s){
        if(c == (char)' '){
            encrypted.push_back((char)' ');
        }
        else{
            idx = 0;
            encrypted.push_back((char)((c+key)%(c+26)));
        }
    }
    return encrypted;
}

vector<char> decryptString(vector<char> encrypted, int key){
    vector<char> decrypted;
    for(auto c : encrypted){
        if(c == (char)' '){
            decrypted.push_back((char)' ');
        }
        else{
            decrypted.push_back((char)((c-key)%(c+26)));
        }
    }

    return decrypted;
}

int main(){
    int choice;
    vector<char> input;
    string inputstr;
    int key;
    vector<char> encrypted;
    vector<char> decrypted;   

    // Creating dict using index as value of key
    for(int i=0; i<26; i++){
        lower.push_back((char) 'a'+i);
    }
    for(int i=0; i<26; i++){
        upper.push_back((char) 'A'+i);
    } 

    while(1){
        cout << "----------OPTIONS-----------" <<endl;
        cout << "1. Encrypt string" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;
        cout << endl;

        switch(choice){

            case 1: 
                cout << "Enter string: " << endl;
                fflush(stdin);
                getline(cin, inputstr);
                for(auto s: inputstr){
                    input.push_back((char)s);
                }

                cout << "Enter key: ";
                cin >> key;

                encrypted = encryptString(input, key);
                cout << "Encrypted string = ";
                for(auto c : encrypted){
                    cout << c;
                }
                cout << "\n\n";
                cout << "----------OPTIONS-----------" <<endl;
                cout << "1. Decrypt string" << endl;
                cout << "2. Continue" << endl;
                cout << "Enter choice: " << endl;
                cin >> choice;
                switch(choice){
                    case 1: 
                    cout << "Decrypted string = ";
                    decrypted = decryptString(encrypted, key);
                    for(auto c : decrypted){
                        cout << c;
                    }
                    cout << "\n\n";
                    break;
                    case 2:
                    break;
                }
                break;
                default: cout << "Wrong choice" << endl;
            case 2:
                exit(0);
        }
    }
    return 0;
}