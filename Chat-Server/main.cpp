#include "Chat.h"

#include "Socket.h"



auto main() -> int
{   
    SocketHandler sock;
    sock.SetupConnect();

    while(true)
    {
    std::string message = sock.getMessage();
    std::cout << message;
    }
    return 0;

}