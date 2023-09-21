/*
 * Author: arefa29
 */

#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>

#define PORT 9034
#define SIZE 1024
#define BACKLOG 5

int main(int argc, char *argv[]){
    int clientfd;
    struct sockaddr_in servAddr;
    char buffer[SIZE];
    bzero(buffer, 1024);
    int n;

    // 1. get hostname and portnumber of server in network byte order
    memset(&servAddr, '\0', sizeof(servAddr));
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(PORT);
    servAddr.sin_family = AF_INET;

    // 2. create socket
    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Client: error in socket creation.\n");
        exit(1);
    } else {
        printf("Client: socket created (%d).\n", clientfd);
    }    

    // 3. connect client socket to server address
    if (connect(clientfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("Client: error in connecting.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Client: connected to %s: %d\n", inet_ntoa(servAddr.sin_addr), ntohs(servAddr.sin_port));
    }

    // 4. chat with the server
    while(1){
        printf("Client: ");
        scanf("%s", buffer);
        send(clientfd, buffer, strlen(buffer), 0);
        bzero(buffer, 1024);

        n = read(clientfd, buffer, 1024);
        if(strcmp(buffer, "exit") == 0){
            printf("Client: connection closed.\n");
            close(clientfd);
            exit(0);
        }
        printf("Server: %s\n", buffer);
        bzero(buffer, 1024);
    }

    return 0;
}