//
// Created by Goblino on 02/01/2022.
//

#define MAX_CONTACTS 100

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#ifndef UNTITLED13_ACCOUNTCLIENT_H
#define UNTITLED13_ACCOUNTCLIENT_H


class AccountClient {
private:

    std::string AccountName = "Undefined";
    std::string AccountPassword = "123456";
    int AccountID = -1;
    std::vector<int> ContactsArray[MAX_CONTACTS];

public:

    AccountClient(
    );

    void CreateAccount(
            std::string accName, std::string accPass, int accID
    );

    void AddContact(int accID);


    ~AccountClient();

};


#endif //UNTITLED13_ACCOUNTCLIENT_H
