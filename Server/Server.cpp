//
// Created by EL Goblino on 02/01/2022.
//

#include "Server.h"


Server::Server() {



    // Inicializacia Server Socketu

    struct sockaddr_in serv_addr;


    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = socDomena;
    serv_addr.sin_addr.s_addr = socProtocol;
    serv_addr.sin_port = htons(port);

    ServerSocket = socket(socDomena, socType, 0);

    if (ServerSocket < 0) {
        std::cout << "ERROR: Error Creating Socket" << std::endl;
        return;
    }

    // Ak je dlzka vysledku nabindovanej adresy mensia ako 0, nastal problem s bindovanym socket adresy
    if (bind(ServerSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "ERROR: Error binding socket address" << std::endl;
        return;
    }

    int maxPossibleConn = 5;

    listen(ServerSocket, maxPossibleConn);

    // Koniec Inicializacie Server Socketu

    appRunning = true;

}

Server::~Server() {
    close(ClientSocket);
    close(ServerSocket);
}

void Server::Run() {

    while (appRunning) {

        std::cout << "Nig" << std::endl;
        socklen_t cli_len;
        struct sockaddr_in cli_addr;
        cli_len = sizeof(cli_addr);

        int n;

        // V nasledujucom kroku cakame na pripojenie klienta
        ClientSocket = accept(ServerSocket, (struct sockaddr *) &cli_addr, &cli_len);
        connectedClients.push_back(ClientSocket);

        std::cout << "Buba" << std::endl;
        std::cout << ClientSocket << std::endl;
        std::cout << ServerSocket << std::endl;


        char *s = inet_ntoa(cli_addr.sin_addr);
        printf("IP address: %s\n", s);

        ipOfClients[countOfConnected] = {
                cli_addr.sin_addr.s_addr,
                cli_addr.sin_port
        };

        countOfConnected++;

        if (ClientSocket < 0) {
            std::cout << "ERROR: Error on accept" << std::endl;
            return;
        }

        std::cout << "Nig" << std::endl;

        const int msg = (int) BufferOutput::RequestLogin;
        n = write(ClientSocket, &msg, sizeof(msg));
        if (n < 0) {
            perror("ERROR: Error writing to socket");
            return;
        }


    }

}

void Server::Listen() {

    while (appRunning > 0) {

        while (countOfConnected > 0) {

            char buffer[256];
            bzero(buffer, 256);

            int n = 0;

            for (int i = 0; i < countOfConnected; ++i) {

                n = read(connectedClients[i], buffer, 255);
                if (n < 0) {
                    perror("Error reading from socket");
                }


                if (buffer[0] != 0) {
                    std::cout << "dsads" << std::endl;

                    int pocitadlo = 1;
                    int countOfWords = 0;
                    int countOfCharsToWrite = 0;
                    std::string meno;
                    std::string heslo;
                    std::string string;
                    int registracneID;
                    int clientSocket = -1;
                    int recvSocket = -1;
                    int loginID = -1;
                    int clientToRemove = -1;
                    int pocitadloIterator = 0;
                    ID_MENO regIDMENO;
                    MESSAGE_TO_RECV messWithRecv;
                    std::string kontakty;
                    std::string message;

                    switch ((BufferInput) buffer[0]) {
                        case BufferInput::CreateAccount:
                            std::cout << "Pokus o vytvorenie" << std::endl;

                            while (buffer[pocitadlo] != 0) {
                                countOfCharsToWrite = buffer[pocitadlo];
                                pocitadlo++;
                                string = std::string(&buffer[pocitadlo], &buffer[pocitadlo + countOfCharsToWrite]);
                                std::cout << string << std::endl;
                                pocitadlo += countOfCharsToWrite;
                                countOfWords++;

                                if (countOfWords == 1) { // Meno
                                    meno = string;
                                } else if (countOfWords == 2) { // Priezvisko
                                    heslo = string;
                                }

                            }

                            registracneID = accountServer.SaveToFile(meno, heslo);

                            // Uspesna Registracia
                            if (registracneID >= 0) {
                                SendMessage(accountServer.SendSuccessRegister(registracneID), connectedClients[i]);
                                // Neuspesna Registracia
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulRegister(), connectedClients[i]);
                            }

                            break;
                        case BufferInput::DeleteAccount:
                            std::cout << "Pokus o zrusenie" << std::endl;
                            clientSocket = connectedClients[i];

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.socket == clientSocket) {
                                    loginID = item.id;
                                    clientToRemove = pocitadloIterator;
                                }
                                pocitadloIterator++;
                            }

                            //Ak by sa stalo, ze nenajde loginID a teda vrati -1, odpoji klienta..., pretoze tu nema co robit

                            registracneID = DeleteRequest(loginID, buffer);

                            if (registracneID >= 0) {
                                loggedInClients.erase(loggedInClients.begin() + clientToRemove);
                                SendMessage(accountServer.SendSuccessDelete(), connectedClients[i]);
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulDelete(), connectedClients[i]);
                            }
                            break;
                        case BufferInput::Login:
                            std::cout << "Pokus o prihlasenie" << std::endl;
                            registracneID = LoginRequest(buffer);

                            if (registracneID >= 0) {

                                loggedInClients.push_back({connectedClients[i], registracneID});

                                countOfLoggedIn++;
                                SendMessage(accountServer.SendSuccessLogin(), connectedClients[i]);
                                // Neuspesny Login
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulLogin(), connectedClients[i]);
                            }

                            break;
                        case BufferInput::LogOut:
                            std::cout << "Pokus o odhlasenie" << std::endl;
                            clientSocket = connectedClients[i];

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.socket == clientSocket) {
                                    loginID = item.id;
                                    clientToRemove = pocitadloIterator;
                                }
                                pocitadloIterator++;
                            }
                            if (clientToRemove > -1) {
                                loggedInClients.erase(loggedInClients.begin() + clientToRemove);
                            }

                            SendMessage(accountServer.SendUnsuccessfulLogOut(), connectedClients[i]);

                            connectedClients.erase(connectedClients.begin() + i);
                            countOfConnected--;
                            break;
                        case BufferInput::Contacts:
                            std::cout << "Pokus o kontakty" << std::endl;
                            break;
                        case BufferInput::SendMessage:
                            std::cout << "Pokus o odoslanie spravy" << std::endl;
                            clientSocket = connectedClients[i];

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.socket == clientSocket) {
                                    loginID = item.id;
                                    clientToRemove = pocitadloIterator;
                                }
                                pocitadloIterator++;
                            }

                            messWithRecv = ProcessMessageToClient(buffer);

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.id == messWithRecv.id) {
                                    recvSocket = item.socket;
                                }
                            }

                            // Prijimatel je online, odosleme mu spravu hned
                            if (recvSocket > -1) {
                                SendMessage(accountServer.SendChatMessageToReceiver(messWithRecv.sprava), recvSocket);
                                SendMessage(accountServer.SendSuccessMessageSend(), connectedClients[i]);
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulMessageSend(), connectedClients[i]);
                            }


                            break;
                        case BufferInput::SendFile:
                            std::cout << "Pokus o odoslanie suboru" << std::endl;
                            break;
                        case BufferInput::GroupMessages:
                            std::cout << "Pokus o odoslanie skupinovej spravy" << std::endl;
                            break;
                        case BufferInput::AddContact:
                            std::cout << "Pokus o pridanie kontaktu" << std::endl;
                            clientSocket = connectedClients[i];

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.socket == clientSocket) {
                                    loginID = item.id;
                                    clientToRemove = pocitadloIterator;
                                }
                                pocitadloIterator++;
                            }

                            regIDMENO = AddContactRequest(loginID, buffer);

                            if (regIDMENO.id > -1) {
                                SendMessage(accountServer.SendSuccessAddContact(regIDMENO.id, regIDMENO.meno),
                                            connectedClients[i]);
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulAddContact(), connectedClients[i]);
                            }

                            break;
                        case BufferInput::RemoveContact:
                            std::cout << "Pokus o vymazanie kontaktu" << std::endl;
                            clientSocket = connectedClients[i];

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.socket == clientSocket) {
                                    loginID = item.id;
                                    clientToRemove = pocitadloIterator;
                                }
                                pocitadloIterator++;
                            }

                            regIDMENO = RemoveContactRequest(loginID, buffer);

                            if (regIDMENO.id > -1) {
                                SendMessage(accountServer.SendSuccessRemoveContact(regIDMENO.id, regIDMENO.meno),
                                            connectedClients[i]);
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulRemoveContact(), connectedClients[i]);
                            }
                            break;
                        case BufferInput::RequestContacts:
                            std::cout << "Pokus o vyziadanie vsetkych kontaktov" << std::endl;

                            clientSocket = connectedClients[i];

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.socket == clientSocket) {
                                    loginID = item.id;
                                    clientToRemove = pocitadloIterator;
                                }
                                pocitadloIterator++;
                            }

                            kontakty = ShowContactsRequest(loginID);

                            SendMessage(accountServer.SendSuccessShowContacts(kontakty), connectedClients[i]);

                            break;
                        default:
                            break;
                    }


                }

            }

            sleep(1);


        }
        sleep(1);
    }

}


void Server::SendMessage(std::string message, int client) {

    char buffer[256];
    bzero(buffer, 256);

    strcpy(buffer, message.c_str());

    int n;

    n = write(client, buffer, BUFF_SIZE);
    if (n < 0) {
        perror("Error writing to socket");
        return;
    }

    std::cout << "Odoslalo: " << std::endl;
    std::cout << (int) buffer[0] << std::endl;
}

int Server::LoginRequest(char *buffer) {

    int pocitadlo = 1;
    int countOfCharsToWrite = 0;
    std::string string;
    int countOfWords = 0;

    std::string meno;
    std::string heslo;

    while (buffer[pocitadlo] != 0) {
        countOfCharsToWrite = buffer[pocitadlo];
        pocitadlo++;
        string = std::string(&buffer[pocitadlo], &buffer[pocitadlo + countOfCharsToWrite]);
        std::cout << string << std::endl;
        pocitadlo += countOfCharsToWrite;
        countOfWords++;

        if (countOfWords == 1) { // Meno
            meno = string;
        } else if (countOfWords == 2) { // Priezvisko
            heslo = string;
        }

    }

    return accountServer.CheckIfExists(meno, heslo, true);
}

int Server::DeleteRequest(int id, char *buffer) {

    int pocitadlo = 1;
    int countOfCharsToWrite = 0;
    std::string heslo;
    int countOfWords = 0;


    while (buffer[pocitadlo] != 0) {
        countOfCharsToWrite = buffer[pocitadlo];
        pocitadlo++;
        heslo = std::string(&buffer[pocitadlo], &buffer[pocitadlo + countOfCharsToWrite]);
        std::cout << heslo << std::endl;
        pocitadlo += countOfCharsToWrite;
    }


    return accountServer.CheckIfExists("", heslo, true, id);
}


ID_MENO Server::AddContactRequest(int loginID, char *buffer) {

    int pocitadlo = 1;
    int countOfCharsToWrite = 0;
    std::string menoKontaktu;
    int countOfWords = 0;

    while (buffer[pocitadlo] != 0) {
        countOfCharsToWrite = buffer[pocitadlo];
        pocitadlo++;
        menoKontaktu = std::string(&buffer[pocitadlo], &buffer[pocitadlo + countOfCharsToWrite]);
        std::cout << menoKontaktu << std::endl;
        pocitadlo += countOfCharsToWrite;
    }

    int idKontaktu = accountServer.SaveToContactsFile(loginID, menoKontaktu);

    return ID_MENO{
            idKontaktu,
            menoKontaktu
    };
}

ID_MENO Server::RemoveContactRequest(int loginID, char *buffer) {
    int pocitadlo = 1;
    int countOfCharsToWrite = 0;
    std::string menoKontaktu;
    int countOfWords = 0;

    while (buffer[pocitadlo] != 0) {
        countOfCharsToWrite = buffer[pocitadlo];
        pocitadlo++;
        menoKontaktu = std::string(&buffer[pocitadlo], &buffer[pocitadlo + countOfCharsToWrite]);
        std::cout << menoKontaktu << std::endl;
        pocitadlo += countOfCharsToWrite;
    }

    int idKontaktu = accountServer.CheckIfExistsInContactsFile(loginID, -1, menoKontaktu, false, -1, true);

    return ID_MENO{
            idKontaktu,
            menoKontaktu
    };
}

std::string Server::ShowContactsRequest(int loginID) {
    return accountServer.LoadContactsFromFileID(loginID);
}

MESSAGE_TO_RECV Server::ProcessMessageToClient(char* buffer) {
    int pocitadlo = 1;
    int countOfCharsToWrite = 0;
    std::string menoKontaktu;
    std::string sprava;
    int countOfWords = 0;

    // Najprv nacitame, komu treba odoslat spravu
    countOfCharsToWrite = buffer[pocitadlo];
    pocitadlo++;
    menoKontaktu = std::string(&buffer[pocitadlo], &buffer[pocitadlo + countOfCharsToWrite]);
    std::cout << menoKontaktu << std::endl;
    pocitadlo += countOfCharsToWrite;
    // Potom nacitame spravu

    sprava = std::string(&buffer[pocitadlo], &buffer[pocitadlo + (BUFF_SIZE - pocitadlo)]);

    int idKontaktu = accountServer.CheckIfExists(menoKontaktu, "", true);

    return MESSAGE_TO_RECV {
            idKontaktu,
            sprava
    };
}



