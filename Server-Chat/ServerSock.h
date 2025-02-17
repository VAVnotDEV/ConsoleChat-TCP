#pragma once
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

class ServerSock
{
    public:
        ServerSock();
        ~ServerSock();
        bool setupConnect();
        int clientConnect();
        std::string receiveMessage();
        void sendMessage(std::string& message);
        void closeClientSocket();
    
    private:
        int _sock_fd, _listener_fd;
        struct sockaddr_in _serverAddr;
        const size_t _BUFFER_SIZE = 1024;
};