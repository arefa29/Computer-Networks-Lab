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

#define PORT 4444 // port users will connect to

#define BACKLOG 10 // number of pending coonnections in queue

#define MAX 100
#define SA struct sockaddr

string decryptRailFence(string cipher_text, int key){

    int rows = key, columns = cipher_text.length();

    // construct rail fence matrix
    char rail[rows][columns];
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            rail[i][j] = '\n';
        }
    }

    // mark '*' in rail matrix
    bool downwards = 1;

    int i=0, j=0;
    for (int k=0; k<cipher_text.length(); k++){
        
        rail[i][j++] = '*';
        if (i == 0) downwards = 1;
        else if (i == rows-1) downwards = 0;

        if (downwards) i++;
        else i--;
    }

    string plain_text;
    int k=0;

    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            if (rail[i][j] == '*' && k<cipher_text.length()){
                rail[i][j] = cipher_text[k];
                k++;
            }
        }
    }

    i=0, j=0;
    for (int k=0; k<cipher_text.length(); k++){

        if (rail[i][j] != '\n')
            plain_text.push_back(rail[i][j++]);

        if (i == 0) downwards = 1;
        else if (i == rows-1) downwards = 0;

        if (downwards) i++;
        else i--;
    }

    return plain_text;
}

// For Chat between client and server, newfd = new socket for new connection
void func(int newfd)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        // read msg from client
        bzero(buff, MAX);
        int count = read(newfd, buff, sizeof(buff));

        // print message from client
        printf("From client: %s", buff);

        char mesg[MAX];
        strcpy(mesg, buff);

        cout << "\nEnter key: ";
        
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;
   
        //decrypt
        int key = buff[0] - '0';
        cout << "Decrypted message: " << decryptRailFence(mesg, key) << endl;

        // if msg contains "exit" then server exit and chat ended
        int i = 0;
        while(decryptRailFence(mesg, key)[i] == "exit"[i] && i <= 4){
            i++;
            if(i == 4){
                printf("Server Exit..\n");
                return;
            }
        }

        // send ack to client that it is still connected
        write(newfd, "c", sizeof("c"));
    }
}
   
// Driver function
int main()
{
    int sockfd, newfd, len;
    struct sockaddr_in servaddr, cliAddr;
   
    // 1. Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed.\n");
        exit(0);
    }
    else
        printf("Socket successfully created.\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // 2. assign IP, PORT address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // 3. Binding newly created socket to given IP and verification
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded.\n");
   
    // 4. Now server is ready to listen 
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed.\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
   
    socklen_t lensock = sizeof(cliAddr);

    for(;;){
        newfd = accept(sockfd, (SA *)&cliAddr, &lensock);
        if (newfd < 0) {
            printf("Server accept failed.\n");
            exit(0);
        }
        else
            printf("\nServer accepted the client %d.\n", newfd);

        // send ack to client that it is connected
        write(newfd, "c", sizeof("c"));

        // Function for chatting between client and server
        func(newfd);

        // After chatting close the socket
        close(newfd);
    }
}
