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

enum class ContactsAction {
    ContactAdded = 1,
    ContactRemoved = 2,
    ShowContacts = 3
};

class Client {

private:
    int socDomena = AF_INET;
    int socType = SOCK_STREAM;
    int port = 87618;

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

    // Spracuje buffer s ID a Menom Kontaktu
    void ProcessBufferContacts(char* buffer);

    void ProcessBufferMessage(char* buffer);

    std::string DecryptMessage(std::string sprava);

};


#endif //UNTITLED13_CLIENT_H
