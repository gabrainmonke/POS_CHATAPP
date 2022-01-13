//
// Created by El Gobol on 02/01/2022.
//

#ifndef UNTITLED13_SUBMENUS_H
#define UNTITLED13_SUBMENUS_H

#define BUFF_SIZE 256

#include <iostream>


class SubMenus {

public:
    SubMenus();
    ~SubMenus();
    int Run(int vstup);
    std::string LoginRegister();
    std::string Login();
    std::string Register();
    std::string AfterLoginMenu();
    std::string DeleteAccount();
    std::string LogOut();
    std::string Contacts();
    std::string AddContact();
    std::string RemoveContact();
    std::string ShowContacts();
    std::string SendChatMessage();
};




#endif //UNTITLED13_SUBMENUS_H
