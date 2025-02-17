#include "ChatServer.h"



auto main() -> int
{   
    SocketHandler sock;
    sock.setupConnect();
    sock.clientConnect();
    std::string message;
    
while(1)
{
    message = sock.receiveMessage();
    std::cout << message << std::endl;
    sock.SendMessage(message);
    if (message == "command_addUser")
    {
        std::cout << "AddUser\n";
    }
    else if (message == "command_authUser")
    {
        std::cout << "authUser\n";
    }
}
    return 0;
}