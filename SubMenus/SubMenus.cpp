//
// Created by El Gobol on 02/01/2022.
//

#include <cstring>
#include "SubMenus.h"

#include "../Variables/BufferInput.cpp"

SubMenus::SubMenus() {}

SubMenus::~SubMenus() {}

int SubMenus::Run(int vstup) {

    int vstupUser = 0;
    std::string vstupUserMessage = "";

    switch (vstup) {
        case 1: // Zrusenie Uctu
            std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

            std::cout << "Zadajte svoje heslo: " << std::endl;

            std::cout << "" << std::endl;
            std::cout << "" << std::endl;

            std::cin >> vstupUserMessage;

            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            std::cout << "SUBMENUS: Ukoncujem program." << std::endl;
            return 7;
        default:
            return 0;

    }

    return 1;

}

std::string SubMenus::LoginRegister() {

    int vstup = 0;
    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

    std::cout << "1. Registrovat sa: " << std::endl;
    std::cout << "2. Prihlasit sa: " << std::endl;

    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    std::cin >> vstup;
    char* test;

    switch (vstup) {
        case 1:
            return Register();
        case 2:
            return Login();
        default:
            return nullptr;
    }

    return 0;
}

std::string SubMenus::Login() {
    int vstup = 0;
    std::string meno = "";
    std::string heslo = "";
    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;
    std::cout << "Prosim prihlaste sa" << std::endl;

    std::cout << "Zadajte meno: ( max 16 znakov ) " << std::endl;

    do {
        std::cin >> meno;
    } while (meno.length() > 16);

    std::cout << "Zadajte heslo ( max 16 znakov ): " << std::endl;

    do {
        std::cin >> heslo;
    } while (heslo.length() > 16);


    std::cout << "Meno: " << meno << std::endl;
    std::cout << "Heslo" << heslo << std::endl;

    char outputBuffer[256];
    bzero(outputBuffer, 256);

    int position = 0;
    outputBuffer[0] = (int) BufferInput::Login;
    position += 1;

    outputBuffer[position] = meno.size();
    position += 1;

    meno.copy(outputBuffer + position, meno.size(), 0);
    position += meno.size();

    outputBuffer[position] = heslo.size();
    position += 1;

    heslo.copy(outputBuffer + position, heslo.size(), 0);
    position += heslo.size();


    return outputBuffer;

}

std::string SubMenus::Register() {
    int vstup = 0;
    std::string meno = "";
    std::string heslo = "";
    std::string hesloZnova = "";
    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

    std::cout << "Zadajte meno: ( max 16 znakov ) " << std::endl;

    do {
        std::cin >> meno;
    } while (meno.length() > 16);

    do {
        std::cout << "Zadajte heslo ( max 16 znakov ): " << std::endl;

        do {
            std::cin >> heslo;
        } while (heslo.length() > 16);

        std::cout << "Zadajte heslo znova ( max 16 znakov ): " << std::endl;

        do {
            std::cin >> hesloZnova;
        } while (hesloZnova.length() > 16);

        if (heslo != hesloZnova) {
            std::cout << "Hesla sa nezhoduju! Skuste znova..." << std::endl;
        }

    } while (heslo != hesloZnova);

    std::cout << "Meno: " << meno << std::endl;
    std::cout << "Heslo" << heslo << std::endl;

    char outputBuffer[256];
    bzero(outputBuffer, 256);

    int position = 0;
    outputBuffer[0] = (int) BufferInput::CreateAccount;
    position += 1;

    outputBuffer[position] = meno.size();
    position += 1;

    meno.copy(outputBuffer + position, meno.size(), 0);
    position += meno.size();

    outputBuffer[position] = heslo.size();
    position += 1;

    heslo.copy(outputBuffer + position, heslo.size(), 0);
    position += heslo.size();


    return outputBuffer;
}

std::string SubMenus::AfterLoginMenu() {
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

    switch (tmpInput) {
        case 1:
            return DeleteAccount();
        default:
            return std::to_string(-1);
    }


}

std::string SubMenus::DeleteAccount() {
    int vstup = 0;
    std::string heslo = "";
    std::string hesloZnova = "";
    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

    do {
        std::cout << "Zadajte heslo ( max 16 znakov ): " << std::endl;

        do {
            std::cin >> heslo;
        } while (heslo.length() > 16);

        std::cout << "Zadajte heslo znova ( max 16 znakov ): " << std::endl;

        do {
            std::cin >> hesloZnova;
        } while (hesloZnova.length() > 16);

        if (heslo != hesloZnova) {
            std::cout << "Hesla sa nezhoduju! Skuste znova..." << std::endl;
        }

    } while (heslo != hesloZnova);

    std::cout << "Heslo: " << heslo << std::endl;

    char outputBuffer[256];

    int position = 0;
    outputBuffer[0] = (int) BufferInput::DeleteAccount;
    position += 1;

    outputBuffer[position] = heslo.size();
    position += 1;

    heslo.copy(outputBuffer + position, heslo.size(), 0);
    position += heslo.size();


    return outputBuffer;
}


