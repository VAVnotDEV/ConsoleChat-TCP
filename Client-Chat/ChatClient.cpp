#include <limits>
#include "SocketHandler.h"
#include "ChatClient.h"



void ChatClient::registerNewUser (std::string login, std::string password)
{
    socket.sendMessage("cmd_RegNewUser");
    std::cout << "\t/ * * Регистрация нового пользователя * */ \n" << "Придумайте логин: "; std::cin >> login;
    std::cin.ignore();
    std::cout << "Придумайте пароль: "; std::getline(std::cin, password);
    socket.sendMessage(login);
    socket.sendMessage(password);
    system("pause");
    system("cls");
}

bool ChatClient::userLogin(std::string login, std::string password)
{

}

void ChatClient::session(int choose)
{
    std::string text, reciever;
    system ("cls");
}