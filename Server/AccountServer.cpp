//
// Created by Goblino on 02/01/2022.
//



#include "AccountServer.h"

#include <iostream>
#include <sstream>


AccountServer::AccountServer(
) {
    FileName = "%APPDATA%/Accounts.txt";
}

void AccountServer::CreateAccount(std::string accName, std::string accPass) {
    this->AccountName = accName;
    this->AccountPassword = accPass;
}


AccountServer::~AccountServer() {

}

bool AccountServer::AddContact(int accID) {
    if (std::find(this->ContactsArray->begin(), this->ContactsArray->end(), accID) != this->ContactsArray->end()) {
        this->ContactsArray->push_back(accID);
        return true;
    }
    return false;
}

bool AccountServer::SaveToFile(std::string pMeno, std::string pHeslo) {
    std::ofstream test;
    test.open("../Files/Accounts.txt", std::fstream::out | std::fstream::in);

    File.open("../Files/Accounts.txt", std::fstream::out | std::fstream::in);

    std::string id;
    std::string meno;
    std::string heslo;

    int idPocitadlo = 0;

    idPocitadlo = CheckIfExists(pMeno, pHeslo);

    if (idPocitadlo != -1) {
        File << idPocitadlo << ';' << pMeno << ';' << pHeslo  << std::endl;
        File.close();
        return true;
    }
    File.close();
    return false;

}

int AccountServer::CheckIfExists(std::string pMeno, std::string pHeslo) {

    int idPocitadlo = 0;

    std::string id;
    std::string meno;
    std::string heslo;

    if (File.is_open()) {
        std::string line;
        std::string splitLine;
        std::stringstream lineInStringStream;

        getline(File, line);
        if (line.empty()) {
            File << "ID;MENO;HESLO" << std::endl;
        }
        do {
            getline(File, line);
            lineInStringStream << line;
            if (!line.empty()) {
                getline(lineInStringStream, splitLine, ';');
                id = splitLine;
                getline(lineInStringStream, splitLine, ';');
                meno = splitLine;
                getline(lineInStringStream, splitLine, '\n');
                heslo = splitLine;

                idPocitadlo++;

                if (meno == pMeno) {
                    // Meno uz existuje
                    return -1;
                }
            }

        } while (!line.empty());
    }

    return idPocitadlo;
}


