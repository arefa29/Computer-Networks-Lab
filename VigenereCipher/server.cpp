/*
 * Author: arefa29
 * Date: Wed Nov 09 2022
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include "encoding.h"
#include<bits/stdc++.h>
using namespace std;

#define PORT 4444 // port users will connect to
#define BACKLOG 10 // number of pending connections in queue
#define MAX 1024

string decryptVigenere(string cipher_text, string key){

    int keylen = key.length();
    int cipherlen = cipher_text.length();

    // repeat the key in the cipher_text
    string intermediate(cipherlen, 0);
    int k=0;
    for(int i=0; i<cipherlen; i++){
        if(cipher_text[i] == ' '){
            intermediate[i] = ' ';
        }
        else {
            intermediate[i] = key[k];
            k = (k+1)%keylen;
        }
    }
    string plain_text(cipherlen, 0);
    for(int k=0; k<cipherlen; k++){
        if(cipher_text[k] == ' '){
            plain_text[k] = ' ';
            continue;
        }
        int diff = cipher_text[k] - intermediate[k];
        if(diff >= 0){
            plain_text[k] = letters[diff];
        }
        else
            plain_text[k] = letters[26+diff];
    }

    return plain_text;
}

// For chat between client and server
void chat(int newfd)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        // read msg from client
        bzero(buff, MAX);
        n = read(newfd, buff, sizeof(buff));
        printf("From client: %s\n", buff);

        // save message before using buff
        char mesg[MAX];
        strcpy(mesg, buff);

        bzero(buff, sizeof(buff));
        printf("Enter the key: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        
        int i = 0;
        string key="";
        for(i = 0; i<n-1; i++){
            key.push_back(buff[i]);
        }

        string decrypted = decryptVigenere(mesg, key);
        cout << "Decrypted message: " << decrypted << endl;

        // if msg contains "exit" then server exit and chat ended
        i = 0;
        while(decrypted[i] == "exit"[i] && i < 4){
            i++;
            if(i == 4){
                printf("Server: Exiting..\n");
                // After chatting close the socket
                close(newfd);
                exit(0);
            }
        }
        // send ack to client that it is still connected
        write(newfd, "message received", sizeof("message received"));
    }
}
   
int main()
{
    int sockfd, newfd, len;
    struct sockaddr_in servAddr, cliAddr;
    socklen_t addrlen = sizeof(cliAddr);
   
    // 1. create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Server: Socket creation failed.\n");
        exit(0);
    }
    else
        printf("Server: Socket successfully created.\n");
    
    // 2. assign IP, PORT address
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(PORT);
   
    // 3. binding socket to given IP
    if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr))) != 0) {
        perror("Server: Socket bind failed...\n");
        exit(0);
    }
    else
        printf("Server: Socket successfully binded.\n");
   
    // 4. listen to incoming connections
    if ((listen(sockfd, 5)) != 0) {
        printf("Server: Listen failed.\n");
        exit(0);
    }
    else
        printf("Server: Server listening..\n");
   
    // 5. accept connections from clients
    for(;;){
        if ((newfd = accept(sockfd, (struct sockaddr *)&cliAddr, &addrlen)) < 0) {
            perror("Server: Server accept failed.\n");
            exit(0);
        }
        else
            printf("Server: Server accepted the client %d.\n", newfd);
        
        Matrix m;

        // send ack to client that it is connected
        write(newfd, "connected", sizeof("connected"));

        // function for chatting between client and server
        chat(newfd);
    }
}