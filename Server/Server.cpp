//
// Created by EL Goblino on 02/01/2022.
//

#include <sys/ioctl.h>
#include "Server.h"
#include <fcntl.h>
#include <poll.h>


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



        socklen_t cli_len;
        struct sockaddr_in cli_addr;
        cli_len = sizeof(cli_addr);

        int n;

        if (pollIn(ServerSocket)) {
            // V nasledujucom kroku cakame na pripojenie klienta
            ClientSocket = accept(ServerSocket, (struct sockaddr *) &cli_addr, &cli_len);

            connectedClients.push_back({ClientSocket, 0});

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

        sleep(1);

    }

}

void Server::Listen() {

    unsigned long ubehnuteSekundy = 0;

    auto t1 = std::chrono::high_resolution_clock::now();

    while (appRunning) {

        auto t1 = std::chrono::high_resolution_clock::now();

        while (countOfConnected > 0) {



            ubehnuteSekundy = 0;

            int n = 0;

            for (int i = 0; i < countOfConnected; ++i) {

                t1 = std::chrono::high_resolution_clock::now();

                char buffer[256];
                bzero(buffer, 256);

                // fcntl(connectedClients[i], F_SETFL, O_NONBLOCK);

                n = recv(connectedClients[i].socket, buffer, 255, MSG_DONTWAIT); //EZ
                if (n < 0) {
                    if (errno == EWOULDBLOCK) {
                      // perror("Nothing to read!\n");


                    } else {
                        std::cout << n << std::endl;
                        perror("Error reading from socket");
                    }
                }

                auto t2 = std::chrono::high_resolution_clock::now();

                std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

                connectedClients[i].afkTime += fp_ms.count() * 100;

                std::cout << "Klient: " << connectedClients[i].socket << " casAFK: " << connectedClients[i].afkTime << std::endl;

                // V tejto vetve bude pribudat AFK Time Klienta

                if (connectedClients[i].afkTime > CLIENT_AFK_THRESHOLD) {

                    int clientToRemove = -1;
                    int pocitadloIterator = 0;

                    for (LOG_IN_CL item: loggedInClients) {
                        if (item.socket == connectedClients[i].socket) {
                            clientToRemove = pocitadloIterator;
                        }
                        pocitadloIterator++;
                    }
                    if (clientToRemove > -1) {
                        loggedInClients.erase(loggedInClients.begin() + clientToRemove);
                    }

                    SendMessage(accountServer.SendSuccessDisconnect(), connectedClients[i].socket);

                    connectedClients.erase(connectedClients.begin() + i);
                    countOfConnected--;
                    break;
                }


                if (buffer[0] != 0) {
                    // Tu sa AFK Time Klienta vynuluje
                    connectedClients[i].afkTime = 0;

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
                    ID_MENO loginIDAMENO;
                    MESSAGE_TO_RECV messWithRecv;
                    std::string kontakty;
                    std::string message;
                    bool alreadyLoggedIn = false;

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
                                SendMessage(accountServer.SendSuccessRegister(registracneID), connectedClients[i].socket);
                                // Neuspesna Registracia
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulRegister(), connectedClients[i].socket);
                            }

                            break;
                        case BufferInput::DeleteAccount:
                            std::cout << "Pokus o zrusenie" << std::endl;
                            clientSocket = connectedClients[i].socket;

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
                                SendMessage(accountServer.SendSuccessDelete(), connectedClients[i].socket);
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulDelete(), connectedClients[i].socket);
                            }
                            break;
                        case BufferInput::Login:
                            std::cout << "Pokus o prihlasenie" << std::endl;
                            loginIDAMENO = LoginRequest(buffer);

                            registracneID = loginIDAMENO.id;

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.id == registracneID) {
                                    std::cout << "Pouzivatel uz je prihlaseny" << std::endl;
                                    alreadyLoggedIn = true;
                                }
                            }

                            if (registracneID >= 0 && !alreadyLoggedIn) {

                                loggedInClients.push_back({connectedClients[i].socket, registracneID, loginIDAMENO.meno});

                                countOfLoggedIn++;
                                SendMessage(accountServer.SendSuccessLogin(), connectedClients[i].socket);
                                // Neuspesny Login
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulLogin(), connectedClients[i].socket);
                            }

                            break;
                        case BufferInput::LogOut:
                            std::cout << "Pokus o odhlasenie" << std::endl;
                            clientSocket = connectedClients[i].socket;

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

                            SendMessage(accountServer.SendUnsuccessfulLogOut(), connectedClients[i].socket);

                            connectedClients.erase(connectedClients.begin() + i);
                            countOfConnected--;
                            break;
                        case BufferInput::Contacts:
                            std::cout << "Pokus o kontakty" << std::endl;
                            break;
                        case BufferInput::SendMessage:
                            std::cout << "Pokus o odoslanie spravy" << std::endl;
                            clientSocket = connectedClients[i].socket;

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.socket == clientSocket) {
                                    loginID = item.id;
                                    clientToRemove = pocitadloIterator;
                                    meno = item.meno;
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
                                SendMessage(accountServer.SendChatMessageToReceiver(messWithRecv.sprava, meno), recvSocket);
                                SendMessage(accountServer.SendSuccessMessageSend(), connectedClients[i].socket);
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulMessageSend(), connectedClients[i].socket);
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
                            clientSocket = connectedClients[i].socket;

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
                                            connectedClients[i].socket);
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulAddContact(), connectedClients[i].socket);
                            }

                            break;
                        case BufferInput::RemoveContact:
                            std::cout << "Pokus o vymazanie kontaktu" << std::endl;
                            clientSocket = connectedClients[i].socket;

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
                                            connectedClients[i].socket);
                            } else {
                                SendMessage(accountServer.SendUnsuccessfulRemoveContact(), connectedClients[i].socket);
                            }
                            break;
                        case BufferInput::RequestContacts:
                            std::cout << "Pokus o vyziadanie vsetkych kontaktov" << std::endl;

                            clientSocket = connectedClients[i].socket;

                            for (LOG_IN_CL item: loggedInClients) {
                                if (item.socket == clientSocket) {
                                    loginID = item.id;
                                    clientToRemove = pocitadloIterator;
                                }
                                pocitadloIterator++;
                            }

                            kontakty = ShowContactsRequest(loginID);

                            SendMessage(accountServer.SendSuccessShowContacts(kontakty), connectedClients[i].socket);

                            break;
                        default:
                            break;
                        case BufferInput::Disconnect:
                            clientSocket = connectedClients[i].socket;

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

                            SendMessage(accountServer.SendSuccessDisconnect(), connectedClients[i].socket);

                            connectedClients.erase(connectedClients.begin() + i);
                            countOfConnected--;
                            break;
                    }


                }

            }

            sleep(1);


        }

        sleep(1);

        auto t2 = std::chrono::high_resolution_clock::now();



        std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

        ubehnuteSekundy += fp_ms.count();


        std::cout << "Ubehlo: " << ubehnuteSekundy / 1000 << std::endl;

        if (ubehnuteSekundy > SERVER_SHUTDOWN_THRESHOLD * 1000) {
            appRunning = false;
        }
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

ID_MENO Server::LoginRequest(char *buffer) {

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

    return {accountServer.CheckIfExists(meno, heslo, true), meno};


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

MESSAGE_TO_RECV Server::ProcessMessageToClient(char *buffer) {
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

    return MESSAGE_TO_RECV{
            idKontaktu,
            sprava
    };
}

// SKOPIROVANE Z - https://stackoverflow.com/questions/62640742/how-to-stop-a-c-blocking-read-call
// Kontroluje ci sa vlastne nieco v sockete nachadza, ak ak vrati true, inak false
bool Server::pollIn(int fd) {
    bool returnValue{false};
    struct pollfd *pfd;
    pfd = static_cast<pollfd *>(calloc(1, sizeof(struct pollfd)));
    pfd->fd = fd;
    pfd->events = POLLIN;

    int pollReturn{-1};
    pollReturn = poll(pfd, 1, 0);

    if (pollReturn > 0)
    {
        if (pfd->revents & POLLIN)
        {
            returnValue = true;
        }
    }
    free(pfd);
    return(returnValue);
}

void Server::Shutdown() {

    for (int i = 0; i < countOfConnected; ++i) {
        SendMessage(accountServer.SendSuccessDisconnect(), connectedClients[i].socket);
    }

}



