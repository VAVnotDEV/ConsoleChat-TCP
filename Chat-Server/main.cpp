#include "ChatServer.h"




auto main() -> int
{   
    SocketHandler sock;
    sock.setupConnect();

    std::string message = sock.receiveMessage();
    std::cout << message;

    if (message == "AddUser")
    {
        std::cout << "Add User";
        

    }

    return 0;

}