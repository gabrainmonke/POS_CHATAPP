//
// Created by El Gobol on 02/01/2022.
//

#include "SubMenus.h"

SubMenus::SubMenus() {}

SubMenus::~SubMenus() {}

int SubMenus::Run(int vstup) {

    int vstupUser = 0;

    switch (vstup) {
        case 1: // Vytvorenie/Zrusenie Uctu
            std::cout << "Vitajte v Chatovej Aplikacii" << std::endl;

            std::cout << "1. Vytvorenie Uctu" << std::endl;
            std::cout << "2. Zrusenie Uctu" << std::endl;

            std::cout << "-- Zadajte vstup: 1-2 --" << std::endl;

            std::cout << "" << std::endl;
            std::cout << "" << std::endl;

            std::cin >> vstupUser;

            if (vstupUser == 1)
            {

            }
            else if (vstupUser == 2)
            {

            }

            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            std::cout << "SUBMENUS: Ukoncujem program." << std::endl;
            return 7;
        default:
            return 0;

    }

    return 1;

}