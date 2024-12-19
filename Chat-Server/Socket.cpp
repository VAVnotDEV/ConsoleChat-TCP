#include "Socket.h"


SocketHandler::SocketHandler()
{
   _server_fd = -1;
}

SocketHandler::~SocketHandler()
{
    std::cout << "Call desctructor\n";
    close(_server_fd);
}

bool SocketHandler::setupConnect()
{
    memset(&_serverAddr, 0, sizeof(_serverAddr));
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    _serverAddr.sin_port = htons(63462);

    _server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_fd < 0)
    {
        perror("Socket creation failed!");
        return false;
    }
    std::cout << "Socket create successful!\n";
    

    if(bind(_server_fd, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) < 0)
    {
        perror("Bind failed!");
        close(_server_fd);
        return false;
    }
    std::cout << "Binding successful!\n";

    if(listen(_server_fd, 5) < 0)
    {
        perror("Listen Failed!");
        close(_server_fd);
        return false;
    }

    std::cout << "Listen successful!\n";
    
    if((_client_fd = accept(_server_fd, NULL, NULL)) == -1)
    {
        perror("Accept failed!");
        exit(3);
        return false;
    }
    std::cout << "Accept successful!\n";
     return true;
}

std::string SocketHandler::receiveMessage()
{
    char buffer[1024];

    if(recv(_client_fd, buffer, 1024,0) < 0)
    {    
    std::cout << "Message not recieve!\n";
    }
    std::cout << buffer << std::endl;
    return buffer;
}

