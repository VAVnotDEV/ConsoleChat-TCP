#include "ChatClient.h"
#include <limits>

int main()
{
    setlocale(LC_ALL, "");
    ChatClient client;
    ClientSock sock;
    sock.serverConnect("127.0.0.1", 63462);

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
                    //client.registerNewUser(login, password);     
                    sock.sendMessage("cmdRegUser");          
                break;
                case LOGIN:
                    sock.sendMessage("cmdAuthUser");
                // if (client.userLogin(login, password))
                // {
                //     client.session(choise);
                // }
                break;
                case EXIT:
                sock.sendMessage("exit");
                        break;
                default:
                std::cout << "Не выбрана команда\n";
                break;
            }
    }
    return 0;

}