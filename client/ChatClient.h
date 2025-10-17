#pragma once
#include <sys/socket.h> //socket
#include <arpa/inet.h> //htonl ntohl
#include <unistd.h>
#include <strings.h>
#include <iostream>
#include <limits>

#define MESSAGE_LENGTH 1024
#define PORT 63462

class ChatClient
{
public:

ChatClient();
~ChatClient();

bool SetupConnection();
bool AuthUser();
bool Register();
void sendData(std::string& s);
void recvData();
void mainLoop();


private:
    enum command { 
        REGISTER = 1, 
        LOGIN, 
        SEND_ALL = 7, 
        LOGOUT = 8, 
        EXIT = 9 };
    
    int choise;    
	int socket_file_descriptor, connection, bytes_read;
	struct sockaddr_in serveraddress, client;
};

