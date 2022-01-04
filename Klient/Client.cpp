//
// Created by EL Goblino on 02/01/2022.
//

#include <netdb.h>
#include <arpa/inet.h>
#include "Client.h"

Client::Client() {

    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    char buffer[256];


    if (server == NULL)
    {
        fprintf(stderr, "ERROR: Error, no such host\n");
        return;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = socDomena;

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    serv_addr.sin_port = htons(port);

    sockfd = socket(socDomena, socType, 0);
    if (sockfd < 0)
    {
        perror("ERROR: Error creating socket");
        return;
    }

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR: Error connecting to socket");
        return;
    }

    /*    printf("Please enter a message: ");
    bzero(buffer,256);

    strcpy(buffer, "Shrek");

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("Error writing to socket");
        return;
    } */

    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        return;
    }

    printf("%s\n",buffer);
    close(sockfd);

    return;
}

Client::~Client() {

}

void Client::Connect() {

}

void Client::Disconnect() {

}
