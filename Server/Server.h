//
// Created by EL Goblino on 02/01/2022.
//

#include <iostream>

#ifndef UNTITLED13_SERVER_H
#define UNTITLED13_SERVER_H

#define MAX_USERS 1024

#define BUFF_SIZE 1024

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


typedef struct IP_ADRESS_AND_PORT {

    unsigned long IPAddress;
    unsigned short Port;

} IP_PORT;

class Server {

private:

    int socDomena = AF_INET;
    int socType = SOCK_STREAM;
    int socProtocol = INADDR_ANY;;

    int port = 87613;

    // SOCKET socketServer;
    // SOCKETADDR_IN address;

    char bufferSend[BUFF_SIZE];
    char bufferListen[BUFF_SIZE];

    IP_PORT ipOfClients[MAX_USERS] = {0};

    bool appRunning = false;

    int ServerSocket;

    int ClientSocket;

public:

    Server();

    ~Server();

    void Run();

    void Listen();


};




#endif //UNTITLED13_SERVER_H
