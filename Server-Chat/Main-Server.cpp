#include "ChatServer.h"



auto main() -> int
{   
    ServerSock sock;
    sock.setupConnect();
    int status = sock.clientConnect();
    std::string message;
    
while(1)
{
    message = sock.receiveMessage();
    std::cout << message << std::endl;
    if (message == "cmdRegUser")
    {   //добавить лоигн и пароль нового пользоватея
        std::cout << "Register_New_User\n";
    }
    else if (message == "cmdAuthUser")
    {
        //Проверка на совпадения логина и пароля, возврат 0 или 1
        std::cout << "AuthUser\n";
    }
} 
    return 0;
}