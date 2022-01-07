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

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

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
            int serverOutput = (buffer[0] - 48);

            switch ((BufferOutput) serverOutput) {

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
                    SendMessage(subMenu.LoginRegister());
                    break;
                case 2:
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
