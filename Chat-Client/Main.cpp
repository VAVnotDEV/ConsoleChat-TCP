#include "ChatClient.h"
#include <limits>

int main()
{
    setlocale(LC_ALL, "");
    ChatClient client;
    // std::string message;
    // while (1)
    // {
    //     std::cin >> message;
    //     if (message == "exit")
    //     {
    //         break;
    //     }
    //     socket.sendMessage(message);
    // }
    // socket.closeSocket();



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
                    client.registerNewUser(login, password);               
                break;
                case LOGIN:
                if (client.userLogin(login, password))
                {
                    client.session(choise);
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