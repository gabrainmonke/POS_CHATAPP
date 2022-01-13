//
// Created by EL Goblino on 02/01/2022.
//

#include <netdb.h>
#include <arpa/inet.h>
#include "Client.h"


#include "../Variables/BufferInput.cpp"

Client::Client() {

    priznakMenu = -1;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];


    if (server == NULL) {
        fprintf(stderr, "ERROR: Error, no such host\n");
        return;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = socDomena;

    serv_addr.sin_addr.s_addr = inet_addr("158.193.128.160");

    serv_addr.sin_port = htons(port);

    sockfd = socket(socDomena, socType, 0);
    if (sockfd < 0) {
        perror("ERROR: Error creating socket");
        return;
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR: Error connecting to socket");
        return;
    }

    clientConnected = true;

    /*    printf("Please enter a message: ");
    bzero(buffer,256);

    strcpy(buffer, "Shrek");

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("Error writing to socket");
        return;
    } */

    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        return;
    }

    std::cout << "Prislo: " << std::endl;
    std::cout << (int) buffer[0] << std::endl;

    switch ((int) buffer[0]) {
        case (int) BufferOutput::RequestLogin:
            SendMessage(subMenu.LoginRegister());
            break;
        default:
            return;
    }

    return;
}

Client::~Client() {

}


void Client::Connect() {

}

void Client::Disconnect() {

}

void Client::SendMessage(std::string message) {

    char buffer[256];
    bzero(buffer, 256);

    strcpy(buffer, message.c_str());

    n = write(sockfd, buffer, BUFF_SIZE);
    if (n < 0) {
        perror("Error writing to socket");
        return;
    }

    std::cout << "Prislo: " << std::endl;
    std::cout << (int) buffer[0] << std::endl;
}

void Client::Listen() {
    while (clientConnected) {

        char buffer[256];
        bzero(buffer, 256);

        int n = 0;
        int id = -1;
        int pocitadlo = 0;
        int poziciaCislaVPoli = 0;
        char numberInCharArray[10];

        n = read(sockfd, buffer, BUFF_SIZE);
        if (n < 0) {
            perror("Error reading from socket");
        }


        if (buffer[0] != 0) {
            std::cout << "dsads" << std::endl;

            // Pride nam cislo ale ako char cize ak nam pride 50 - je to 2ka, takze my musime odpocitat 48
            char serverOutput = buffer[0];

            // veryPoggers - Jest Cislo tak odpocita, Jest znak tak nech tak. Poggers.

            switch ((buffer[0] >= 48 && buffer[0] <= 57 ? (BufferOutput) (int) (serverOutput - 48)
                                                        : (BufferOutput) serverOutput)) {

                case BufferOutput::RequestLogin:
                    break;
                case BufferOutput::RegistrationSuccess:
                    std::cout << "REGISTER SUCCESSFULLO" << std::endl;

                    pocitadlo = 1;
                    id = -1;


                    bzero(numberInCharArray, 10);

                    while (buffer[pocitadlo] != 0) {
                        numberInCharArray[poziciaCislaVPoli] = buffer[pocitadlo];
                        poziciaCislaVPoli++;
                        pocitadlo++;
                    }

                    id = atoi(numberInCharArray);

                    std::cout << "Vratene ID" << std::to_string(id) << std::endl;

                    priznakMenu = 1;

                    break;
                case BufferOutput::RegistrationUnsuccessful:
                    std::cout << "REGISTRADO UNSUCEFSZA" << std::endl;

                    priznakMenu = 2;
                    break;
                case BufferOutput::LoginSuccess:
                    std::cout << "LOGIN SUCCESSFULLO" << std::endl;
                    priznakMenu = 3;
                    break;
                case BufferOutput::LoginUnsuccessful:
                    std::cout << "LOGINDO UNSUCEFSZA" << std::endl;
                    priznakMenu = 1;
                    break;
                case BufferOutput::DeleteSuccess:
                    std::cout << "DELETO SUCCESSFULLO" << std::endl;
                    priznakMenu = 2;
                    break;
                case BufferOutput::DeleteUnsuccessful:
                    std::cout << "DELETO UNSUCEFSZA" << std::endl;
                    priznakMenu = 3;
                    break;
                case BufferOutput::LogoutSuccessful:
                    std::cout << "LOGOUTO SUCCESSFULLO" << std::endl;
                    priznakMenu = 4;
                    break;
                case BufferOutput::AddContactSuccessful:
                    std::cout << "CONTACTO ADDENDO SUCCESSFULLO" << std::endl;
                    priznakMenu = 5;
                    break;
                case BufferOutput::AddContactUnsuccessful:
                    std::cout << "CONTACTO ADDENDO UNSUCEFSZA" << std::endl;
                    priznakMenu = 5;
                    break;
                case BufferOutput::RemoveContactSuccessful:
                    std::cout << "CONTACTO REMOVEDO SUCCESSFULLO" << std::endl;
                    priznakMenu = 5;
                    break;
                case BufferOutput::RemoveContactUnsuccessful:
                    std::cout << "CONTACTO REMOVEDO UNSUCEFSZA" << std::endl;
                    priznakMenu = 5;
                    break;
                case BufferOutput::RequestContactsSuccessful:
                    std::cout << "CONTACTO SHOWO SUCCESSFULLO" << std::endl;
                    ProcessBufferContacts(buffer);
                    priznakMenu = 5;
                    break;
                case BufferOutput::SendingMessage:
                    std::cout << "MESSAGE RECIVENDO SUCCESSFULLO" << std::endl;
                    ProcessBufferMessage(buffer);
                    priznakMenu = 3;
                    break;
                case BufferOutput::SendMessageSuccessful:
                    std::cout << "MESSAGE SENDO SUCCESSFULLO" << std::endl;
                    priznakMenu = 3;
                    break;
                case BufferOutput::SendMessageUnsuccessful:
                    std::cout << "MESSAGE SENDO UNSUCEFSZA" << std::endl;
                    priznakMenu = 3;
                    break;
            }
            bzero(buffer, BUFF_SIZE);
        }


        sleep(1);


    }

}

void Client::Menu() {

    while (clientConnected) {

        if (priznakMenu != -1) {

            switch (priznakMenu) {
                case 1:
                    SendMessage(subMenu.Login());
                    break;
                case 2:
                    SendMessage(subMenu.LoginRegister());
                    break;
                case 3:
                    SendMessage(subMenu.AfterLoginMenu());
                    break;
                case 4:
                    clientConnected = false;
                    break;
                case 5:
                    SendMessage(subMenu.Contacts());
                    break;

            }

            // Pri prijati spravy si bude treba pamat aj predosly priznak
            // To znamena, ze ked prijde sprava - priznak sa nastavy na napr. 5 - vypise spravu aj odosielatela
            // Ponukne X-nut spravu
            // A po xnuti sa nastavy predosly priznak a zobrazi sa napr menu LoginRegister, ak bolo pred tym otvorene, alebo nejake ine, ktore bolo
            // otvorene

            priznakMenu = -1;
        }
        sleep(1);
    }

}

void Client::ProcessBufferContacts(char *buffer) {

    int pocitadlo = 1;
    int countOfCharsToWrite = 0;
    std::string string;
    int countOfWords = 0;

    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

    std::cout << "Zoznam kontakov:" << std::endl;

    std::cout << "" << std::endl;

    while (buffer[pocitadlo] != 0) {
        countOfCharsToWrite = buffer[pocitadlo] - 48;
        pocitadlo++;
        string = std::string(&buffer[pocitadlo], &buffer[pocitadlo + countOfCharsToWrite]);
        pocitadlo += countOfCharsToWrite;
        countOfWords++;

        std::cout << "- - - " << string << std::endl;

    }

    std::cout << "" << std::endl;

}

void Client::ProcessBufferMessage(char *buffer) {
    int pocitadlo = 1;
    int countOfCharsToWrite = 0;
    std::string string;
    int countOfWords = 0;

    string = std::string(&buffer[pocitadlo], &buffer[pocitadlo + (BUFF_SIZE - pocitadlo)]);
    pocitadlo += countOfCharsToWrite;
    countOfWords++;

    std::string::size_type poziciaNullCharu = string.find((char)0);

    string = string.substr(0, poziciaNullCharu);

    std::cout << "SPRAVA: " <<  string << std::endl;
}
