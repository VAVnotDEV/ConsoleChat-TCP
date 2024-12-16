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

bool SocketHandler::SetupConnection(const std::string& ip, const int& port)
{
    if(_sock_fd = socket(AF_INET, SOCK_STREAM, 0) == -1)
    {
        perror("Socket created failed!");
        return false;
    }

    std::cout << "Socket created\n";

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(63462);
    inet_pton(AF_INET, "5.53.20.189", &_addr.sin_addr);

    if ((connect(_sock_fd, (struct sockaddr*)&_addr, sizeof(_addr))) == -1)
    {
        perror("Connect error");
        return false;
    }
    std::cout << "Connection sucefull!\n";
    return true;
}

void SocketHandler::SendMessage()
{
    char message[1024] = "Hello world";
    send(_sock_fd, message, strlen(message),0);
}