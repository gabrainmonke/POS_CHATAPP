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
// find zacne od zaciatku a do konca a porovanam ho s tym co je na konci, to znamena ze pokial ho najde, tak to vrati ukazovatel na to miesto.
// nie zle hovoris, ono v podstate neporovnama s tym co je na konci ale ci uz je to konicec
// lebo tebe vracia adresu toho vektora

bool AccountClient::AddContact(int accID) {
    if (std::find(this->ContactsArray->begin(), this->ContactsArray->end(), accID) != this->ContactsArray->end()) {
        this->ContactsArray->push_back(accID);
        return true;
    }
    return false;
}


