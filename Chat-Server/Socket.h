#pragma once
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

class SocketHandler
{
    public:
        SocketHandler();
        ~SocketHandler();
        bool SetupConnect();
        bool ClientConnect();
        std::string getMessage();
        void SendMessage(std::string message);
    
    private:
        int _server_fd, _client_fd;
        struct sockaddr_in _serverAddr;
};