#include "ChatServer.h"




auto main() -> int
{   
    SocketHandler sock;
    sock.setupConnect();
    sock.clientConnect();
    std::string message;
while(sock.clientConnect())
{
    message = sock.receiveMessage();
    std::cout << message;
    if (message == "command_addUser")
    {
        std::cout << "AddUser\n";
    }
    else if (message == "command_authUser")
    {
        std::cout << "authUser\n";
    }
    else
    {
        std::cout << message;
    }
}
    return 0;
}