#include <iostream>
#include "Server/Server.h"
#include "Klient/Client.h"
#include "SubMenus/SubMenus.h"

#include <thread>

int main() {


    SubMenus subMenus;

    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

    std::cout << "1. Server" << std::endl;
    std::cout << "2. Client" << std::endl;

    std::cout << "-- Zadajte vstup: 1-2 --" << std::endl;

    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    int vstupServerKlient = 0;
    std::cin >> vstupServerKlient;

    if (vstupServerKlient == 1) {
        Server server;
        std::thread tmpThreadForListening(&Server::Run, &server);
        std::thread tmpThreadForListeningClients(&Server::Listen, &server);

        std::cout << "Pokusam sa spustit Server" << std::endl;

        tmpThreadForListening.join();
        tmpThreadForListeningClients.join();
    } else {
        bool ukonci = false;
        do {
            Client client;
            std::thread tmpClientThreadForListening(&Client::Listen, &client);
            std::thread tmpClientThreadForMenu(&Client::Menu, &client);

            std::cout << "Pokusam sa spustit Klienta" << std::endl;

            tmpClientThreadForListening.join();
            tmpClientThreadForMenu.join();

            std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

            std::cout << "" << std::endl;
            std::cout << "" << std::endl;

            std::cout << "1. Pokracovat naspat do applikacie" << std::endl;
            std::cout << "2. Vypnut aplikaciu" << std::endl;

            std::cout << "" << std::endl;

            int tmpInput = 0;

            std::cout << "-- Zadajte vstup: 1-2 --" << std::endl;
            std::cin >> tmpInput;
            std::cout << "-- Zadali ste: " << tmpInput << "." << std::endl;

            if (tmpInput == 2) {
                ukonci = true;
            }

        } while (!ukonci);

        // Ak sme spustili Server, interakcia konci...
        if (vstupServerKlient == 1) {
            return 0;
        }

    }
}
