//
// Created by Goblino on 02/01/2022.
//

#define MAX_CONTACTS 100

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fstream>


#ifndef UNTITLED13_ACCOUNTCLIENT_H
#define UNTITLED13_ACCOUNTCLIENT_H


class AccountServer {
private:

    std::string AccountName = "Undefined";
    std::string AccountPassword = "123456";
    int AccountID = -1;
    std::vector<int> ContactsArray[MAX_CONTACTS];
    std::string FileName = "";
    std::fstream FileAccounts;
    std::fstream FileContacts;

public:

    AccountServer(
    );

    void CreateAccount(
            std::string accName, std::string accPass
    );

    bool AddContact(int accID);

    int SaveToFile(std::string pMeno, std::string pHeslo);

    int SaveToContactsFile(int mojeID, std::string menoKontaktu);

    int CheckIfExists(std::string pMeno, std::string pHeslo = "", bool onlyCheck = false, int pId = -1);

    int CheckIfExistsInContactsFile(int mojeID, int idKontaktu, std::string menoKontaktu, bool onlyCheck = false, int pId = -1, bool parDelete = false);

    std::string EncryptPass(std::string pass);

    std::string DecryptPass(std::string pass);

    std::string LoadContactsFromFileID(int mojeID);

    std::string SendSuccessRegister(int ID);

    std::string SendUnsuccessfulRegister();

    std::string SendSuccessLogin();

    std::string SendUnsuccessfulLogin();

    std::string SendSuccessDelete();

    std::string SendUnsuccessfulDelete();

    std::string SendUnsuccessfulLogOut();

    std::string SendSuccessAddContact(int idKontaktu, std::string menoKontaktu);

    std::string SendUnsuccessfulAddContact();

    std::string SendSuccessRemoveContact(int idKontaktu, std::string menoKontaktu);

    std::string SendUnsuccessfulRemoveContact();

    std::string SendSuccessShowContacts(std::string contacts);

    std::string SendChatMessageToReceiver(std::string message);

    std::string SendSuccessMessageSend();

    std::string SendUnsuccessfulMessageSend();





    ~AccountServer();

};


#endif //UNTITLED13_ACCOUNTCLIENT_H
