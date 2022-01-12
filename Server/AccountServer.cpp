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
    FileAccounts.open("Accounts.txt", std::ios::out | std::ios::in | std::ios::app);

    std::string id;
    std::string meno;
    std::string heslo;

    int idPocitadlo = 0;

    idPocitadlo = CheckIfExists(pMeno, pHeslo);

    if (idPocitadlo != -1) {
        FileAccounts << std::to_string(idPocitadlo) + ";" + pMeno + ";" + pHeslo + "\n";
        //FileAccounts.write(dataAccount.data(), dataAccount.size());
        FileAccounts.close();
        return idPocitadlo;
    }
    FileAccounts.close();
    return -1;

}

int AccountServer::CheckIfExists(std::string pMeno, std::string pHeslo, bool onlyCheck, int pId) {

    int idPocitadlo = 1;

    std::string id;
    std::string meno;
    std::string heslo;

    int oldPos = 0;

    if (onlyCheck && !FileAccounts.is_open()) {
        FileAccounts.open("Accounts.txt", std::ios::out | std::ios::in );
    }

    if (FileAccounts.is_open()) {
        std::string line;
        std::string splitLine;
        std::stringstream lineInStringStream;
        getline(FileAccounts, line);
        FileAccounts.clear();
        FileAccounts.seekg(0);
        if (line.empty()) {
            // FileAccounts.write(identifier.data(), identifier.size());
            FileAccounts << "ID;MENO;HESLO\n";
        } else {
            getline(FileAccounts, line);
        }
        do {
            oldPos = FileAccounts.tellg();
            getline(FileAccounts, line);
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
                        FileAccounts.clear();
                        FileAccounts.seekg(oldPos);
                        std::string invalidLine = "-1;-1;-1";
                        invalidLine.resize(line.size());
                        FileAccounts << invalidLine << std::endl;
                        return numberID;
                    } else if ((meno == pMeno) && (heslo == pHeslo)) {
                        return std::stoi(id);
                    } else if ((pHeslo.empty()) && (meno == pMeno)) {
                        return std::stoi(id);
                    }



                } else if (!onlyCheck && (meno == pMeno)) {
                    // Meno uz existuje
                    return -1;
                }

            }

        } while (!line.empty());
    }

    FileAccounts.clear();
    FileAccounts.seekg(oldPos);

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

std::string AccountServer::SendUnsuccessfulLogOut() {
    std::string logOutSucc = std::to_string((int)BufferOutput::LogoutSuccessful);
    return logOutSucc;
}


std::string AccountServer::SendSuccessAddContact(int idKontakt, std::string menoKontaktu) {
    std::string AddContSucc = std::to_string((int)BufferOutput::AddContactSuccessful);
    AddContSucc += std::to_string(idKontakt);
    AddContSucc += std::to_string(menoKontaktu.size());
    AddContSucc += menoKontaktu;
    return AddContSucc;
}

std::string AccountServer::SendUnsuccessfulAddContact() {
    char charakter = static_cast<char>(BufferOutput::AddContactUnsuccessful);
    std::string AddContUnsucc( 1, charakter);
    return AddContUnsucc;
}

std::string AccountServer::SendSuccessShowContacts(std::string contacts) {
    char charakter = static_cast<char>(BufferOutput::RequestContactsSuccessful);
    std::string ShowContSucc( 1, charakter);
    ShowContSucc += contacts;
    return ShowContSucc;
}

int AccountServer::SaveToContactsFile(int mojeID, std::string menoKontaktu) {
    FileContacts.open("Contacts/" + std::to_string(mojeID), std::ios::out | std::ios::in | std::ios::app);

    std::string id;
    std::string meno;
    std::string heslo;

    int idKontaktu = -1;

    int idPocitadlo = 0;

    idKontaktu = CheckIfExists(menoKontaktu, "", true); // Kontroluje v subore MIEN/HESIEL - Accounts.txt

    if (idKontaktu <= -1) {
        return -1;
    }

    idPocitadlo = CheckIfExistsInContactsFile(mojeID, idKontaktu, menoKontaktu);

    if (idPocitadlo != -1) {
        FileContacts << std::to_string(idKontaktu) + ";" + menoKontaktu + "\n";
        //FileAccounts.write(dataAccount.data(), dataAccount.size());
        FileContacts.close();
        return idKontaktu;
    }
    FileContacts.close();
    return -1;
}

int AccountServer::CheckIfExistsInContactsFile(int mojeID, int idKontaktu, std::string menoKontaktu, bool onlyCheck,
                                               int pId, bool parDelete) {
    int idPocitadlo = 1;

    std::string id;
    std::string meno;
    std::string heslo;

    long oldPos = 0;

    if ((onlyCheck || parDelete) && !FileContacts.is_open()) {
        FileContacts.open("Contacts/" + std::to_string(mojeID), std::ios::out | std::ios::in );
    }

    if (FileContacts.is_open()) {
        FileContacts.clear();
        FileContacts.seekg(0);
    }

    if (FileContacts.is_open()) {
        std::string line;
        std::string splitLine;
        std::stringstream lineInStringStream;
        getline(FileContacts, line);
        FileContacts.clear();
        FileContacts.seekg(0);
        if (line.empty()) {
            // FileAccounts.write(identifier.data(), identifier.size());
            FileContacts << "ID;MENO\n";
        } else {
            getline(FileContacts, line);
        }
        do {
            oldPos = FileContacts.tellg();
            getline(FileContacts, line);
            lineInStringStream.clear();
            lineInStringStream << line;
            if (!line.empty()) {
                getline(lineInStringStream, splitLine, ';');
                id = splitLine;
                getline(lineInStringStream, splitLine, '\n');
                meno = splitLine;

                idPocitadlo++;
                int numberID = std::stoi(id);

                if (parDelete) {
                    if ((meno == menoKontaktu)) {
                        FileContacts.clear();
                        FileContacts.seekg(oldPos);
                        std::string invalidLine = "-1;-1";
                        invalidLine.resize(line.size());

                        for (int i = 0; i < invalidLine.size(); ++i) {
                            if (((invalidLine[i] != (char)('-')) && (invalidLine[i] != (char)('1')) && (invalidLine[i] != (char)(';')))) {
                                invalidLine[i] = 0;
                            }
                        }

                        FileContacts << invalidLine << std::endl;
                        return numberID;
                    }
                    if (onlyCheck ) {
                    } if ((meno == menoKontaktu)) {
                        return std::stoi(id);
                    }

                } else if (!onlyCheck && (meno == menoKontaktu)) {
                    // Meno uz existuje
                    return -1;
                }

            }

        } while (!line.empty());
    }

    FileContacts.clear();
    FileContacts.seekg(oldPos);

    if (onlyCheck || parDelete) {
        FileContacts.close();
        return -1;
    } else {
        return idPocitadlo;
    }
}

std::string AccountServer::SendSuccessRemoveContact(int idKontaktu, std::string menoKontaktu) {
    char charakter = static_cast<char>(BufferOutput::RemoveContactSuccessful);
    std::string RemoveContSucc(1, charakter);
    RemoveContSucc += std::to_string(idKontaktu);
    RemoveContSucc += std::to_string(menoKontaktu.size());
    RemoveContSucc += menoKontaktu;
    return RemoveContSucc;
}

std::string AccountServer::SendUnsuccessfulRemoveContact() {
    char charakter = static_cast<char>(BufferOutput::RemoveContactUnsuccessful);
    std::string RemoveContUnsucc(1, charakter);
    return RemoveContUnsucc;
}

std::string AccountServer::LoadContactsFromFileID(int mojeID) {


    std::string returnString;

    FileContacts.open("Contacts/" + std::to_string(mojeID), std::ios::out | std::ios::in | std::ios::app);

    int idPocitadlo = 1;

    std::string id;
    std::string meno;
    std::string heslo;

    int oldPos = 0;

    if (!FileContacts.is_open()) {
        FileContacts.open("Contacts/" + std::to_string(mojeID), std::ios::out | std::ios::in );
    }

    if (FileContacts.is_open()) {
        std::string line;
        std::string splitLine;
        std::stringstream lineInStringStream;
        getline(FileContacts, line);
        FileContacts.clear();
        FileContacts.seekg(0);
        if (line.empty()) {
            // FileAccounts.write(identifier.data(), identifier.size());
            FileContacts << "ID;MENO\n";
        } else {
            getline(FileContacts, line);
        }
        do {
            oldPos =  FileContacts.tellg();
            getline(FileContacts, line);
            lineInStringStream.clear();
            lineInStringStream << line;
            if (!line.empty()) {
                getline(lineInStringStream, splitLine, ';');
                id = splitLine;
                getline(lineInStringStream, splitLine, '\n');
                meno = splitLine;

                idPocitadlo++;

                if ( (meno[0] != '-' && meno[1] != '1') &&  !meno.empty()) {
                    returnString += std::to_string(meno.size()) + meno;
                }



            }

        } while (!line.empty());
    }

    FileContacts.clear();
    FileContacts.seekg(oldPos);

    FileContacts.close();

    return returnString;
}







