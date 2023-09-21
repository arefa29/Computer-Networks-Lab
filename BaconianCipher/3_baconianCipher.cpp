#include <bits/stdc++.h>
using namespace std;

string encryptMessage(string inputMsg, string sent){

    vector<char> abEncryption(5*inputMsg.length());
    vector<int> bin(5*inputMsg.length(), 0);
    int num;
    int k=0;
    char c;
    int len = inputMsg.length();

    for(int i=0; i<inputMsg.length(); i++){

        if(inputMsg[i] == ' ') {
            continue;
        }
        // if letter is capital
        if(inputMsg[i] - 'a' < 0) c = 'A';
        // if small
        else c = 'a';

        num = (inputMsg[i] - c);

        for(int j=4; j>=0; j--){
            bin[j+k] = num % 2;
            num = num / 2;
        }
        k += 5;
    }
    for(int i=bin.size()-1; i>=k; i--){
        bin.pop_back(); //remove the extra 0's from the end
    }

    for(int i=0; i<bin.size(); i++){
        if(bin[i] == 0){
            abEncryption[i] = 'a';
        }
        else {
            abEncryption[i] = 'b';
        }
    }
    abEncryption.resize(k);

    string encryptedSent;
    int j=0;

    for(int i=0; i<abEncryption.size(); i++){

        if(sent[j] == ' ') j++;

        if(abEncryption[i] == 'a'){
            if('A' <= sent[j] && sent[j] <= 'Z'){
                // convert to lowercase
                encryptedSent.push_back(char(sent[j] - 'A' + 'a'));
            }
            else {
                encryptedSent.push_back(char(sent[j]));
            }
        }
        else {
            if('a' <= sent[j] && sent[j] <= 'z'){
                // convert to uppercase
                encryptedSent.push_back(char(sent[j] - 'a' + 'A'));
            }
            else {
                encryptedSent.push_back(char(sent[j]));
            }
        }
        j = (j+1) % sent.length();
    }

    return encryptedSent;
}

string decryptMessage(string encrypted){

    vector<int> bin;

    for(int i=0; i<encrypted.length(); i++){
        if(encrypted[i] >= 'a' && encrypted[i] <= 'z'){
            bin.push_back(0);
        }
        else {
            bin.push_back(1);
        }
    }

    string decrypted;
    int j = 0;
    int num = 0;
    int mult = 1;

    for(int i=0; i<bin.size(); i += 5){
        num=0;
        mult=1;
        for(j=i+4; j>=i; j--){
            num += bin[j]*mult;
            mult *= 2;
        }
        decrypted.push_back('a' + num);
    }
    return decrypted;
}

int main(){

    cout << "Name: Arefa\nRoll No: 20BCS074\n\n";

    int choice;
    string inputMessage;
    string sentence;
    string encrypted;
    string decrypted;
    int incorrect=0;

    while(1){

        cout << "-------------OPTIONS---------------"<<endl;
        cout << "1. Encrypt message\n";
        cout << "2. Decrypt message\n";
        cout << "3. Exit\n";
        fflush(stdin);
        cin >> choice;

        switch (choice)
        {
        case 1:
            inputMessage.clear();
            sentence.clear();
            cout << "\nEnter message to be encrypted: ";
            fflush(stdin);
            getline(cin, inputMessage);
            cout << "\nEnter sentence for encryption: ";
            fflush(stdin);
            getline(cin, sentence);

            for(int i=0; i<inputMessage.length(); i++){
                if('a' <= inputMessage[i] && inputMessage[i] <= 'z' || 'A' <= inputMessage[i] && inputMessage[i] <= 'Z' || inputMessage[i] == ' ');
                else {
                    cout << "Special characters and numbers not allowed!\n";
                    incorrect = 1;
                    break;
                }
            }
            if(incorrect) continue;

            encrypted =  encryptMessage(inputMessage, sentence);
            cout << "\nEncrypted message: " << encrypted << endl;
            break;
        case 2:
            decrypted = decryptMessage(encrypted);
            cout << "\nDecrypted message: " << decrypted << endl;
            break;
        case 3:
            exit(0);
        default:
            cout << "WRONG CHOICE!\n";
            break;
        }
    }
    return 0;
}