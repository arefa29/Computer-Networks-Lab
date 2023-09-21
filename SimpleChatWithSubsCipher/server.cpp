/*
 * Author: arefa29
 * simple chat with substitution cipher
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
#include <fcntl.h>
using namespace std;

#define PORT 8082 // port server is listening on
#define SIZE 1024
#define BACKLOG 5

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
    int sockfd, newfd, rv;
    struct sockaddr_in servAddr, newAddr;
    socklen_t addrlen = sizeof(newAddr);
    char buffer[SIZE];
    int n;

    vector<char> input;
    string inputstr;
    int key;
    vector<char> encrypted;
    vector<char> decrypted; 

    // 1. create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Server: error in socket creation.\n");
        exit(1);
    } else {
        printf("Server: socket created.\n");
    }

    // 2. address to bind socket to
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // using local IP
    servAddr.sin_port = htons(PORT);

    // 3. bind the socket to port
    if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr))) < 0) {
        perror("Server: error in binding.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Server: socket bound.\n");
    }

    // 4. listen for incoming connection requests
    if ((listen(sockfd, BACKLOG)) < 0) {
        perror("Server: error in listening.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Server: listening.\n");
    }

    // 5. accept connections
    for(;;){
        if ((newfd = accept(sockfd, (struct sockaddr *) &newAddr, &addrlen)) < 0){
            perror("Server: error in accepting.\n");
            exit(EXIT_FAILURE);
        } else {
            printf("Server: connection accepted from %s: %d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
        }

        // 6. send ack to client that it is connected
        write(newfd, "connected", sizeof("connected"));

        // 7. chat with the client
        while(1){
            bzero(buffer, 1024);
            rv = read(newfd, buffer, sizeof buffer);

            cout << "Server: Enter key: ";
            cin >> key;
            for(auto c: buffer){
                encrypted.push_back(c);
            }
            decrypted = decryptString(encrypted, key);

            bzero(buffer, sizeof buffer);
            int i=0;
            for(auto c: decrypted){
                buffer[i++] = c;
            }
            buffer[i] = '\0';

            if(strcmp(buffer, "exit") == 0){
                printf("Server: connection closed.\n");
                close(sockfd);
                exit(0);
            }
            printf("Client: %s\n", buffer);

            bzero(buffer, 1024);
            printf("Server: ");
            scanf("%s", buffer);
            send(newfd, buffer, strlen(buffer), 0);
            bzero(buffer, 1024);
        }
    }
    return 0;
}