//
// Created by EL Goblino on 02/01/2022.
//

#include "Server.h"


Server::Server() {


    // Inicializacia Server Socketu

    struct sockaddr_in serv_addr;


    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = socDomena;
    serv_addr.sin_addr.s_addr = socProtocol;
    serv_addr.sin_port = htons(port);

    ServerSocket = socket(socDomena, socType, 0);

    if (ServerSocket < 0) {
        std::cout << "ERROR: Error Creating Socket" << std::endl;
        return;
    }

    // Ak je dlzka vysledku nabindovanej adresy mensia ako 0, nastal problem s bindovanym socket adresy
    if (bind(ServerSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "ERROR: Error binding socket address" << std::endl;
        return;
    }

    int maxPossibleConn = 5;

    listen(ServerSocket, maxPossibleConn);

    // Koniec Inicializacie Server Socketu

    appRunning = true;

}

Server::~Server() {
    close(ClientSocket);
    close(ServerSocket);
}

void Server::Run() {

    while (appRunning) {

        std::cout << "Nig" << std::endl;
        socklen_t cli_len;
        struct sockaddr_in cli_addr;
        cli_len = sizeof(cli_addr);

        int n;

        // V nasledujucom kroku cakame na pripojenie klienta
        ClientSocket = accept(ServerSocket, (struct sockaddr *) &cli_addr, &cli_len);

        std::cout << "Buba" << std::endl;
        std::cout << ClientSocket << std::endl;
        std::cout << ServerSocket << std::endl;


        char *s = inet_ntoa(cli_addr.sin_addr);
        printf("IP address: %s\n", s);


        if (ClientSocket < 0) {
            std::cout << "ERROR: Error on accept" << std::endl;
            return;
        }

        std::cout << "Nig" << std::endl;

        const char *msg = "Uspesne pripojeny na server";
        n = write(ClientSocket, msg, strlen(msg) + 1);
        if (n < 0) {
            perror("ERROR: Error writing to socket");
            return;
        }

    }

}


