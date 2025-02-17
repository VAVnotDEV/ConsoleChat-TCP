#include "ServerSock.h"


ServerSock::ServerSock()
{
   _sock_fd = -1;
}

ServerSock::~ServerSock()
{
    std::cout << "Call desctructor\n";
    close(_sock_fd);
}

bool ServerSock::setupConnect()
{
    memset(&_serverAddr, 0, sizeof(_serverAddr));
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    _serverAddr.sin_port = htons(63462);

    _listener_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_listener_fd < 0)
    {
        perror("Socket creation failed!");
        return false;
    }
    std::cout << "Socket create successful!\n";
    

    if(bind(_listener_fd, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) < 0)
    {
        perror("Bind failed!");
        return false;
    }
    std::cout << "Binding successful!\n";

    if(listen(_listener_fd, 5) < 0)
    {
        perror("Listen Failed!");
        return false;
    }
    std::cout << "Listen successful!\n";
     return true;
}

int ServerSock::clientConnect()
{
    if((_sock_fd = accept(_listener_fd, NULL, NULL)) == -1)
    {
        perror("Accept failed!");
        return -1;
    }
    std::cout << "Accept successful!\n";
    return 1;
    
}

std::string ServerSock::receiveMessage()
{
    char buffer[_BUFFER_SIZE];
    size_t bytes_read = recv(_sock_fd, buffer, sizeof(buffer),0);
    if( bytes_read  < 0)
    {    
    perror("Message not recieve!");
    return "";
    }
    else if (bytes_read == 0)
    {
        std::cout << "Connect close";
        closeClientSocket();
        return "exit";
    }
    else std::cout << "Message recieve\n";
    return buffer;
}

void ServerSock::sendMessage(std::string& message)
{
    
    send(_sock_fd, message.c_str(), _BUFFER_SIZE,0);
}

void ServerSock::closeClientSocket()
{
    std::cout << "Connect client close" << std::endl;
    close(_sock_fd);
}
