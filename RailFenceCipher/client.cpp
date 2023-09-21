/*
 * Author: arefa29
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
#include<bits/stdc++.h>
using namespace std;

#define MAX 100
#define PORT 4444
#define SA struct sockaddr

string encryptRailFence(string plain_text, int key){

    // rail fence matrix: 
    int rows = key, columns = plain_text.length();
    char rail[rows][columns];

    // mark the matrix with initial values
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            rail[i][j] = '\n';
        }
    }

    // keep track of whether we want to go downwards
    bool downwards = 1;

    // move diagonally down and up:
    int i=0;
    int k=0;
    for (int j=0; j<columns; j++){

        rail[i][j] = plain_text[k++];

        if (i == rows-1) downwards = 0;
        else if (i == 0) downwards = 1;

        if (downwards) i++;
        else i--;
    }

    string cipher_text;
    k = 0;

    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            if(rail[i][j] != '\n'){
                cipher_text.push_back(rail[i][j]);
                k++;
            }
        }
    }

    return cipher_text;
}

void func(int sockfd)
{
    char buff[MAX];
    char data[10];
    int n;
    for (;;) {

        // recv ack from server to check if still connected
        if ((n = read(sockfd, data, sizeof(data))) == 0){
            printf("\nConnection closed by server.\n");
            return;
        }

        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        
        // Encrypt
        string plain="";
        for(int i=0; i<n-1; i++){
            plain.push_back(buff[i]);
        }

        bzero(buff, sizeof(buff));
        printf("Enter the key: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        
        int key = buff[0] - '0';
        string enc = encryptRailFence(plain, key);
        char encmsg[MAX];

        int i=0;
        for (i=0; i<enc.length(); i++){
            encmsg[i] = enc[i];
        }
        encmsg[i] = '\0';

        // send cipher text
        write(sockfd, encmsg, sizeof(encmsg));

        bzero(buff, sizeof(buff));
        bzero(data, sizeof(data));
    }
}
 
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed.\n");
        exit(0);
    }
    else
        printf("Socket created.\n");
    bzero(&servaddr, sizeof(servaddr));
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("Connection with the server failed.\n");
        exit(0);
    }
    else
        printf("Connected to the server.\n");
 
    // function for chat
    func(sockfd);
 
    // close the socket
    close(sockfd);
}