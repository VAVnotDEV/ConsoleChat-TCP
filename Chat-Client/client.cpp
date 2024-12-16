#include <iostream>
#include <string>
#include <limits>
#include "SocketHandler.h"

void f_registerNewUser (std::string& login, std::string& password)
{
                    std::cout << "\t/ * * Регистрация нового пользователя * */ \n" << "Придумайте логин: "; std::cin >> login;
                    std::cin.ignore();
                    std::cout << "Придумайте пароль: "; std::getline(std::cin, password);
                        //отправка данных на сервер
                    system("pause");
                    system("cls");
}
void f_UserLogin(std::string& login, std::string& password)
{

}
void session(int choose)
{
    std::string text, reciever;
    system ("cls");
}

auto main() -> int
{ 
    SocketHandler sock;
        sock.SendMessage();
    setlocale(LC_ALL, "");
    enum command {REGISTER = 1, LOGIN, SEND_ALL = 7, LOGOUT = 8, EXIT = 9};
    auto choise = 0;
    std::string login, password;

    while (choise != EXIT)
    {
        std::cout << "\n\t****Консольный чат****\n" << REGISTER << ".Регистрация\n" << LOGIN << ".Вход" << EXIT << ".Выход\n" << "Введите команду : ";
        std::cin >> choise;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choise)
            {
                case REGISTER:
                    f_registerNewUser(login, password);               
                break;
                case LOGIN:
                if (f_UserLogin(login, password) == true)
                {
                    session(choise);
                }
                break;
                case EXIT:
                        break;
                default:
                std::cout << "Не выбрана команда\n";
                break;
            }
    }
    return 0;
}