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
        Client client;
        std::thread tmpClientThreadForListening(&Client::Listen, &client);
        std::thread tmpClientThreadForMenu(&Client::Menu, &client);
        tmpClientThreadForListening.join();
        tmpClientThreadForMenu.join();
    }

    // Ak sme spustili Server, interakcia konci...
    if (vstupServerKlient == 1) {
        return 0;
    }

    std::cout << "Pokusam sa spustit Klienta" << std::endl;

    // Inak Klient Logika

    bool ukonci = false;

    while (!ukonci) {

        std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

        std::cout << "" << std::endl;
        std::cout << "" << std::endl;

        std::cout << "1. Zruste Ucet" << std::endl;
        std::cout << "2. Odhlasit Sa" << std::endl;
        std::cout << "3. Kontakty" << std::endl;
        std::cout << "4. Poslat spravu" << std::endl;
        std::cout << "5. Poslat subor" << std::endl;
        std::cout << "6. Skupinove konverzacie" << std::endl;

        std::cout << "" << std::endl;
        std::cout << "" << std::endl;

        std::cout << "7. Vypnut" << std::endl;

        int tmpInput = 0;

        std::cout << "-- Zadajte vstup: 1-7 --" << std::endl;
        std::cin >> tmpInput;
        std::cout << "-- Zadali ste: " << tmpInput << "." << std::endl;

        subMenus.Run(tmpInput) == 7 ? ukonci = true : ukonci = false;

    }


}
