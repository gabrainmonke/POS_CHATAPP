//
// Created by El Gobol on 02/01/2022.
//

#include <cstring>
#include <iosfwd>
#include <fstream>
#include "SubMenus.h"
#include <sys/stat.h>

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
    char *test;

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
        case 2:
            return LogOut();
        case 3:
            return Contacts();
        case 4:
            return SendChatMessage();
        default:
            return std::to_string((char)-1);
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
    bzero(outputBuffer, 256);

    int position = 0;
    outputBuffer[0] = (int) BufferInput::DeleteAccount;
    position += 1;

    outputBuffer[position] = heslo.size();
    position += 1;

    heslo.copy(outputBuffer + position, heslo.size(), 0);
    position += heslo.size();


    return outputBuffer;
}

std::string SubMenus::LogOut() {

    char outputBuffer[256];
    bzero(outputBuffer, 256);

    outputBuffer[0] = (int) BufferInput::LogOut;
    return outputBuffer;

}

std::string SubMenus::Contacts() {
    int vstup = 0;
    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

    std::cout << "1. Pridat Kontakt: " << std::endl;
    std::cout << "2. Zmazat Kontakt " << std::endl;
    std::cout << "3. Vypisat Kontakty " << std::endl;

    std::cout << "0. Navrat spat " << std::endl;

    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    std::cin >> vstup;

    switch (vstup) {
        case 1:
            return AddContact();
        case 2:
            return RemoveContact();
        case 3:
            return ShowContacts();
        default:
            return AfterLoginMenu();
    }

    return 0;
}

std::string SubMenus::AddContact() {
    int vstup = 0;
    std::string meno = "";
    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;


    std::cout << "Zadajte meno kontaktu pre pridanie. ( max 16 znakov ): " << std::endl;

    do {
        std::cin >> meno;
    } while (meno.length() > 16);


    char outputBuffer[256];
    bzero(outputBuffer, 256);

    int position = 0;
    outputBuffer[0] = (int) BufferInput::AddContact;
    position += 1;

    outputBuffer[position] = meno.size();
    position += 1;

    meno.copy(outputBuffer + position, meno.size(), 0);
    position += meno.size();

    return outputBuffer;
}

std::string SubMenus::RemoveContact() {
    int vstup = 0;
    std::string meno = "";
    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;


    std::cout << "Zadajte meno kontaktu pre odstránenie. ( max 16 znakov ): " << std::endl;

    do {
        std::cin >> meno;
    } while (meno.length() > 16);


    char outputBuffer[256];
    bzero(outputBuffer, 256);

    int position = 0;
    outputBuffer[0] = (int) BufferInput::RemoveContact;
    position += 1;

    outputBuffer[position] = meno.size();
    position += 1;

    meno.copy(outputBuffer + position, meno.size(), 0);
    position += meno.size();

    return outputBuffer;
}

std::string SubMenus::ShowContacts() {
    int vstup = 0;

    char outputBuffer[256];
    bzero(outputBuffer, 256);

    int position = 0;
    outputBuffer[0] = (int) BufferInput::RequestContacts;
    position += 1;

    return outputBuffer;
}

std::string SubMenus::SendChatMessage() {
    int vstup = 0;
    std::string meno = "";
    std::string sprava  = "";
    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;


    std::cout << "Zadajte meno kontaktu na odoslanie. ( max 16 znakov ): " << std::endl;

    do {
        std::cin >> meno;
    } while (meno.length() > 16);



    char outputBuffer[256];
    bzero(outputBuffer, 256);

    int position = 0;
    outputBuffer[0] = (int) BufferInput::SendMessage;
    position += 1;

    outputBuffer[position] = meno.size();
    position += 1;

    meno.copy(outputBuffer + position, meno.size(), 0);
    position += meno.size();

    std::cout << "Zadajte spravu: " << std::endl;

    std::getline(std::cin >> std::ws, sprava);

    sprava = EncryptMessage(sprava);

    sprava.copy(outputBuffer + position, sprava.size(), 0);

    return outputBuffer;
}

std::string SubMenus::SendFile() {
    int vstup = 0;
    std::string cestaKSuboru = "";
    std::string zapisanySubor  = "";
    std::string meno  = "";
    FILE* subor;
    std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

    std::cout << "Zadajte meno kontaktu na odoslanie. ( max 16 znakov ): " << std::endl;

    do {
        std::cin >> meno;
    } while (meno.length() > 16);

    std::cout << "Zadajte cestu k súboru: " << std::endl;

    do {
        std::cin >> cestaKSuboru;

    } while (!CheckIfFileExists(cestaKSuboru));

    subor = fopen(cestaKSuboru.c_str(), "r");

    char outputBuffer[256];
    bzero(outputBuffer, 256);

    int position = 0;
    outputBuffer[0] = (int) BufferInput::SendFile;
    position += 1;

    outputBuffer[position] = meno.size();
    position += 1;

    meno.copy(outputBuffer + position, meno.size(), 0);
    position += meno.size();


    char riadokArray[BUFF_SIZE - position - 16 - sizeof(int)];
    bzero(riadokArray, BUFF_SIZE - position - 16 - sizeof(int));

    std::string riadok;

    while (fgets(riadokArray, BUFF_SIZE - position, subor)) {
        zapisanySubor += riadokArray;
    }

    // zapisanySubor = fgets(riadokArray, BUFF_SIZE - position, subor);

    zapisanySubor.copy(outputBuffer + position, zapisanySubor.size(), 0);
    position += zapisanySubor.size();

    fclose(subor);

    return outputBuffer;
}

bool SubMenus::CheckIfFileExists(const std::string& cesta) {
        std::ifstream file(cesta.c_str());
        if (!file.good()) {
            std::cout << "Subor Neexistuje Zadajte Znova " << std::endl;
        }

        size_t size = 0;

        struct stat st;
        if (stat (cesta.c_str(), &st) == 0){
            size =  st.st_size;
        }

        if (size > 235) {
            std::cout << "Subor presahuje maximalnu velkost bytov (235) " << std::endl;
        }

        if (size <= 235) {
            return file.good();
        } else {
            return false;
        }


}

std::string SubMenus::EncryptMessage(std::string sprava) {
    for (int i = sprava.size(); i > 0; i--) {
        sprava[i] = sprava[i] + i + 1;
    }
    std::cout << "DECRIPTANDO: " << sprava << std::endl;
    return sprava;
}



