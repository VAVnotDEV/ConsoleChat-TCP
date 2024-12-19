#include "ChatServer.h"

#include "Socket.h"



auto main() -> int
{   
    SocketHandler sock;
    sock.setupConnect();

    while(1)
    {
        
    std::string message = sock.receiveMessage();
    std::cout << message;

    if (message == "REGISTER")
    {

    }

    }

    return 0;

}