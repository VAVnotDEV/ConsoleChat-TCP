#include "ClientSock.h"

ClientSock::ClientSock()
{
    _sock_fd = -1;
}

ClientSock::~ClientSock()
{
    closeSocket();
}

bool ClientSock::serverConnect(const std::string ip, const int port)
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

bool ClientSock::sendMessage(const std::string& message)
{
    return send(_sock_fd, message.c_str(), message.size(),0) != -1;
}

std::string ClientSock::receiveMessage()
{
    const size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    if(recv(_sock_fd, buffer, sizeof(buffer), 0) < 0)
    {
        perror("Receive failed");
    }
    return buffer;
}

void ClientSock::closeSocket()
{
    close (_sock_fd);
    _sock_fd = -1;
}