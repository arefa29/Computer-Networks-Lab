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

#define MAX 1024
#define PORT 4444

string encryptVigenere(string plain_text, string key){

    int keylen = key.length();
    int plainlen = plain_text.length();

    // convert to lowercase
    for(int i=0; i<plainlen; i++){
        if(plain_text[i] >= 'A' && plain_text[i] <= 'Z'){
            plain_text[i] = 'a' + plain_text[i] - 'A';
        }
    }

    // repeat the key in the plain_text
    string intermediate(plainlen, 0);
    int k=0;
    for(int i=0; i<plainlen; i++){
        if(plain_text[i] == ' '){
            intermediate[i] = ' ';
        }
        else {
            intermediate[i] = key[k];
            k = (k+1)%keylen;
        }
    }

    int i, j;
    string cipher_text(plainlen, 0);
    for(int k=0; k<plainlen; k++){

        if(plain_text[k] == ' '){
            cipher_text[k] = ' ';
            continue;
        }
        i = plain_text[k] - 'a'; // 0 - 25
        j = intermediate[k] - 'a'; // 0 - 25

        cipher_text[k] = letters[matrix[i][j]-1];
    }

    return cipher_text;
}

void chat(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        // recv ack from server to check if still connected
        if ((n = read(sockfd, buff, sizeof(buff))) == 0){
            printf("Client: Connection closed by server.\n");
            return;
        }
        else {
            printf("Server: %s\n", buff);
        }

        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n') ;
        
        // save input text
        string plain="";
        int i = 0;
        for(i = 0; i<n-1; i++){
            plain.push_back(buff[i]);
        }

        bzero(buff, sizeof(buff));
        printf("Enter the key: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        
        string key="";
        for(i = 0; i<n-1; i++){
            key.push_back(buff[i]);
        }

        string enc = encryptVigenere(plain, key);

        // convert string to char * for sending
        char encmsg[MAX];
        for (i = 0; i < enc.length(); i++){
            encmsg[i] = enc[i];
        }
        encmsg[i] = '\0';

        // send cipher text
        write(sockfd, encmsg, sizeof(encmsg));

        bzero(buff, sizeof(buff));
    }
}
 
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servAddr, cli;
 
    // create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Client: Socket creation failed.\n");
        exit(0);
    }
    else
        printf("Client: Socket created.\n");
         
    // assign IP, PORT
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(PORT);
 
    // connect the client socket to server socket
    if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr))!= 0) {
        perror("Client: Connection with the server failed.\n");
        exit(0);
    }
    else
        printf("Client: Connected to the server.\n");

    // create instance of Matrix class
    Matrix m;
    // function for chat
    chat(sockfd);
 
    // close the socket
    close(sockfd);
}