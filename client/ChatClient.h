#pragma once
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using SocketType = SOCKET;
#else
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //htonl ntohl
#include <unistd.h>
using SocketType = int;
#endif

#include "Message.h"
#include "DataExchangeProtocol.h"

#define MESSAGE_LENGTH 1024
#define PORT 63462


class ChatClient
{
public:

    ChatClient();
    ~ChatClient();

    bool SetupConnection();


    bool sendData();
    bool recvData();

    bool AuthUser();
    bool userRegister();
    void getListUser();
    void showListUser();
    void showAllMessages();
    void sendMessage();
    void recvMessageFrom();
    void recvAllMessageFrom();
    void resetState();
    void mainLoop();


private:
    enum command { 
        REGISTER = 1, 
        LOGIN, 
        SEND_ALL = 7, 
        LOGOUT = 8, 
        EXIT = 9 };

    DataExchangeProtocol _dep;
    std::string _currentUser;
    
    std::vector<Message<std::string>>_messages;
    std::vector<std::string>_contacts;
    
    std::string _currentCMD;
    bool _bGetListUsers = true;


    int _choise;    
    SocketType _socket_file_descriptor;
	int  _connection, _bytes_read;
	struct sockaddr_in _serveraddress, _client;
    
};

