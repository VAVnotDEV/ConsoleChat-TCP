#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>

#define MESSAGE_LENGTH 1024
#define PORT 63462

class SocketHandler
{
public:
    void SetupConnect();
    void connect();
    void sendData();
    void recvData();

private:
    struct sockaddr_in serveraddress, client;
    socklen_t length;
    int sockert_file_descriptor, connection, bind_status, connection_status;
    char message[MESSAGE_LENGTH];

};