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
    std::fstream File;

public:

    AccountServer(
    );

    void CreateAccount(
            std::string accName, std::string accPass
    );

    bool AddContact(int accID);

    int SaveToFile(std::string pMeno, std::string pHeslo);

    int CheckIfExists(std::string pMeno, std::string pHeslo, bool onlyCheck = false, int pId = -1);

    std::string SendSuccessRegister(int ID);

    std::string SendUnsuccessfulRegister();

    std::string SendSuccessLogin();

    std::string SendUnsuccessfulLogin();

    std::string SendSuccessDelete();

    std::string SendUnsuccessfulDelete();


    ~AccountServer();

};


#endif //UNTITLED13_ACCOUNTCLIENT_H
