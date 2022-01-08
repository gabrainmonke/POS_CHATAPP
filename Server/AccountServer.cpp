//
// Created by Goblino on 02/01/2022.
//



#include "AccountServer.h"

#include <iostream>
#include <sstream>

#include "../Variables/BufferInput.cpp"

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

int AccountServer::SaveToFile(std::string pMeno, std::string pHeslo) {
    File.open("Accounts.txt", std::ios::out | std::ios::in | std::ios::app);

    std::string id;
    std::string meno;
    std::string heslo;

    int idPocitadlo = 0;

    idPocitadlo = CheckIfExists(pMeno, pHeslo);

    if (idPocitadlo != -1) {
        File << std::to_string(idPocitadlo) + ";" + pMeno + ";" + pHeslo + "\n";
        //File.write(dataAccount.data(), dataAccount.size());
        File.close();
        return idPocitadlo;
    }
    File.close();
    return -1;

}

int AccountServer::CheckIfExists(std::string pMeno, std::string pHeslo, bool onlyCheck, int pId) {

    int idPocitadlo = 1;

    std::string id;
    std::string meno;
    std::string heslo;

    int oldPos = 0;

    if (onlyCheck && !File.is_open()) {
        File.open("Accounts.txt", std::ios::out | std::ios::in );
    }

    if (File.is_open()) {
        std::string line;
        std::string splitLine;
        std::stringstream lineInStringStream;
        getline(File, line);
        File.clear();
        File.seekg(0);
        if (line.empty()) {
            // File.write(identifier.data(), identifier.size());
            File << "ID;MENO;HESLO\n";
        } else {
            getline(File, line);
        }
        do {
            oldPos =  File.tellg();
            getline(File, line);
            lineInStringStream.clear();
            lineInStringStream << line;
            if (!line.empty()) {
                getline(lineInStringStream, splitLine, ';');
                id = splitLine;
                getline(lineInStringStream, splitLine, ';');
                meno = splitLine;
                getline(lineInStringStream, splitLine, '\n');
                heslo = splitLine;

                idPocitadlo++;
                int numberID = std::stoi(id);

                if (onlyCheck ) {
                    if (pId > 0 && (pId == numberID) && (heslo == pHeslo)) {
                        File.clear();
                        File.seekg(oldPos);
                        std::string invalidLine = "-1;-1;-1";
                        invalidLine.resize(line.size());
                        File << invalidLine << std::endl;
                        return numberID;
                    } else if ((meno == pMeno) && (heslo == pHeslo)) {
                        return std::stoi(id);
                    }



                } else if (!onlyCheck && (meno == pMeno)) {
                    // Meno uz existuje
                    return -1;
                }

            }

        } while (!line.empty());
    }

    File.clear();
    File.seekg(oldPos);

    if (onlyCheck) {
        return -1;
    } else {
        return idPocitadlo;
    }

}

std::string AccountServer::SendSuccessRegister(int ID) {
    std::string regSucc = std::to_string((int)BufferOutput::RegistrationSuccess) + std::to_string(ID);
    return regSucc;
}

std::string AccountServer::SendUnsuccessfulRegister() {
    std::string regSucc = std::to_string((int)BufferOutput::RegistrationUnsuccessful);
    return regSucc;
}

std::string AccountServer::SendSuccessLogin() {
    std::string logSucc = std::to_string((int)BufferOutput::LoginSuccess);
    return logSucc;
}

std::string AccountServer::SendUnsuccessfulLogin() {
    std::string logUnsucc = std::to_string((int)BufferOutput::LoginUnsuccessful);
    return logUnsucc;
}

std::string AccountServer::SendSuccessDelete() {
    std::string delSucc = std::to_string((int)BufferOutput::DeleteSuccess);
    return delSucc;
}

std::string AccountServer::SendUnsuccessfulDelete() {
    std::string delUnsucc = std::to_string((int)BufferOutput::DeleteUnsuccessful);
    return delUnsucc;
}



