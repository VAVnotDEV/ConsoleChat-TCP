#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

class SocketHandler
{
    public:
    SocketHandler();
    ~SocketHandler();
    bool CreateSocket();
    void SendMessage();

    private:
    int _sock_fd;
    struct sockaddr_in _addr;

};