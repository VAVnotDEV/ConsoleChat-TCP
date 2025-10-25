#pragma once
#include <sys/socket.h> //socket
#include <arpa/inet.h> //htonl ntohl
#include <unistd.h>
#include <iostream>
#include <vector>
#include "../Message.h"
#include "../DataExchangeProtocol.h"

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
    std::vector<std::string>_to;
    
    std::string _currentCMD;
    bool _bGetListUsers = true;


    int _choise;    
	int _socket_file_descriptor, _connection, _bytes_read;
	struct sockaddr_in _serveraddress, _client;
    
};

