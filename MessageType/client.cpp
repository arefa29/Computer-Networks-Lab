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

int main(){
    int clientfd;
    struct sockaddr_in servAddr;
    char buffer[SIZE];
    bzero(buffer, 1024);
    int n;

    // 0. get hostname and portnumber of server in network byte order
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(PORT);
    servAddr.sin_family = AF_INET;

    // 1. create socket
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
        // recv ack from server to check if still connected
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
        write(clientfd, buffer, sizeof(buffer));
        bzero(buffer, sizeof buffer);
    }
    return 0;
}
