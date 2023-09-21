/*
 * Author: arefa29
 */

#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
using namespace std;

#define PORT 8082
#define SIZE 1024

// encrypt using substitution cipher
vector<char> encryptString(vector<char> s, int key){
    vector<char> encrypted;
    
    for(auto c : s){
        if(c == (char)' '){
            encrypted.push_back((char)' ');
        }
        else{
            encrypted.push_back((char)((c+key)%(c+26)));
        }
    }
    return encrypted;
}

int main(){
    int clientfd;
    struct sockaddr_in servAddr;
    char buffer[SIZE];
    bzero(buffer, 1024);
    int n;

    vector<char> input;
    string inputstr;
    int key;
    vector<char> encrypted;
    vector<char> decrypted;  

    // 1. get hostname and portnumber of server in network byte order
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(PORT);
    servAddr.sin_family = AF_INET;

    // 2. create socket
    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Client: error in socket creation.\n");
        exit(1);
    } else {
        printf("Client: socket created.\n");
    }    

    // 3. connect client socket to server address
    if ((connect(clientfd, (struct sockaddr *)&servAddr, sizeof(servAddr))) != 0) {
        perror("Client: error in connecting.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Client: connected to %s: %d\n", inet_ntoa(servAddr.sin_addr), ntohs(servAddr.sin_port));
    }

    // 4. chat with the server
    while(1){
        // 5. recv ack from server to check if still connected
        n = read(clientfd, buffer, sizeof(buffer));
        if (n == 0){
            printf("Client: connection closed by server.\n");
            close(clientfd);
                exit(0);
        }
        else {
            printf("Server: %s\n", buffer);
        }
        
        bzero(buffer, sizeof buffer);
        printf("Client: ");
        scanf("%s", buffer);

        // encrypt
        for(auto s: buffer){
            input.push_back((char)s);
        }
        cout << "Client: Enter key: ";
        cin >> key;
        encrypted = encryptString(input, key);

        bzero(buffer, sizeof buffer);
        int i=0;
        for(auto c: encrypted){
            buffer[i++] = c;
        }
        buffer[i] = '\0';
        
        write(clientfd, buffer, sizeof(buffer));
        bzero(buffer, sizeof buffer);
    }
    return 0;
}