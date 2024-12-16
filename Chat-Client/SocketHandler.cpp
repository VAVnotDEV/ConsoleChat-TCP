#include "SocketHandler.h"

SocketHandler::SocketHandler()
{
}

SocketHandler::~SocketHandler()
{
    if(_sock_fd != -1)
    {
    close(_sock_fd);
    }
}

bool SocketHandler::SetupConnection(const std::string ip, const int port)
{

    _sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sock_fd < 0)
    {
        perror("Socket create successful");
        return false;
    }
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &_addr.sin_addr);
    if(connect(_sock_fd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
    {
        perror("Connect error");
        return false;
    }
    std::cout << "Connect successful!\n";
    return true;
}

void SocketHandler::SendMessage()
{
    char message[1024] = "Hello world";
    //send(sock, message, strlen(message),0);
}