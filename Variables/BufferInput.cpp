//
// Created by Gobl on 02/01/2022.
//

enum class BufferInput {
    Disconnect = '-',
    CreateAccount = 1,
    DeleteAccount = 2,
    Login = 3,
    LogOut = 4,
    Contacts = 5,
    SendMessage = 6,
    SendFile = 7,
    GroupMessages = 8,
    AddContact = 9,
    RemoveContact = 'a',
    RequestContacts = 'b'
};

enum class BufferOutput {
    RequestLogin = 1,
    RegistrationSuccess = 2,
    RegistrationUnsuccessful = 3,
    LoginSuccess = 4,
    LoginUnsuccessful = 5,
    DeleteSuccess = 6,
    DeleteUnsuccessful = 7,
    LogoutSuccessful = 8,
    AddContactSuccessful = 9,
    AddContactUnsuccessful = 'a',
    RemoveContactSuccessful = 'b',
    RemoveContactUnsuccessful = 'c',
    RequestContactsSuccessful = 'd',
    SendingMessage = 'e',
    SendMessageSuccessful = 'f',
    SendMessageUnsuccessful = 'g',
    DisconnectSucc = 'h',
};