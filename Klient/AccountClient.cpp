//
// Created by Goblino on 02/01/2022.
//



#include "AccountClient.h"

#include <iostream>

AccountClient::AccountClient(
) {
}

void AccountClient::CreateAccount(std::string accName, std::string accPass, int accID) {
    this->AccountName = accName;
    this->AccountPassword = accPass;
    this->AccountID = accID;
}


AccountClient::~AccountClient() {

}

void AccountClient::AddContact(int accID) {
    // this->ContactsArray.
}


