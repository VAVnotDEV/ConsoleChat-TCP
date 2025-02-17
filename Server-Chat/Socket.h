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
        bool setupConnect();
        int clientConnect();
        std::string receiveMessage();
        void SendMessage(std::string& message);
    
    private:
        int _sock_fd, _listener_fd;
        struct sockaddr_in _serverAddr;
        const size_t _BUFFER_SIZE = 1024;
};