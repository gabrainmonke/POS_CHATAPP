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
};




#endif //UNTITLED13_SUBMENUS_H
