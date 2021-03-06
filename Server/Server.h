//
// Created by EL Goblino on 02/01/2022.
//

#include <iostream>


#include "AccountServer.h"
#include "../Variables/BufferInput.cpp"
#include <thread>

#ifndef UNTITLED13_SERVER_H
#define UNTITLED13_SERVER_H

#define MAX_USERS 1024

#define BUFF_SIZE 256

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

typedef struct LOGGED_IN_CLIENT {
    int socket;
    int id;
} LOG_IN_CL;

typedef struct ID_A_MENO_KONTAKTU {
    int id;
    std::string meno;
} ID_MENO;

typedef struct MESSAGE_WITH_RECEIVER{
    int id;
    std::string sprava;
} MESSAGE_TO_RECV;

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

    std::vector<int> connectedClients;

    std::vector<LOG_IN_CL> loggedInClients;

    int countOfConnected = 0;

    int countOfLoggedIn = 0;

    bool appRunning = false;

    int ServerSocket;

    int ClientSocket;

    AccountServer accountServer;

public:

    Server();

    ~Server();

    void Run();

    void Listen();

    void SendMessage(std::string message, int client);

    int LoginRequest(char* buffer);

    int DeleteRequest(int id , char* buffer);

    ID_MENO AddContactRequest(int loginID, char *buffer);

    ID_MENO RemoveContactRequest(int loginID, char *buffer);

    std::string ShowContactsRequest(int loginID);

    MESSAGE_TO_RECV ProcessMessageToClient(char *buffer);

    // pep
};




#endif //UNTITLED13_SERVER_H
