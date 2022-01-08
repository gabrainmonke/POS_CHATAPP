//
// Created by EL Goblino on 02/01/2022.
//

#include <iostream>



#ifndef UNTITLED13_CLIENT_H
#define UNTITLED13_CLIENT_H

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
#include "../SubMenus/SubMenus.h"

class Client {

private:
    int socDomena = AF_INET;
    int socType = SOCK_STREAM;
    int port = 87614;

    char bufferSend[BUFF_SIZE];
    char bufferListen[BUFF_SIZE];

    int sockfd;
    int n;

    bool clientConnected = false;

    SubMenus subMenu;

    int priznakMenu;

public:
    Client();

    ~Client();

    void Connect();

    void Disconnect();

    void SendMessage(std::string message);

    void Listen();

    void Menu();

};


#endif //UNTITLED13_CLIENT_H
