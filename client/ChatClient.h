#pragma once
#include <sys/socket.h> //socket
#include <arpa/inet.h> //htonl ntohl
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>

#define MESSAGE_LENGTH 1024
#define PORT 63462

class ChatClient
{
private:
    struct ChatCommandData
	{	
		//CMD:LOG:LOGIN:PASSWORD:TO:FROM:TEXTMESSAGE
		std::string cmd;
		std::string log;
		std::string login;
		std::string password;
		std::string to;
		std::string from;
		std::string textMessage;	

        void DataClear();
        void showData();
    };
    
public:

    ChatClient();
    ~ChatClient();

    bool SetupConnection();

	void inputDataHandler(char* ch1, int n);
	void outputDataHandler(char* ch1);
    bool sendData();
    bool recvData();

    bool AuthUser();
    bool userRegister();
    void listUser();
    void mainLoop();


private:
    enum command { 
        REGISTER = 1, 
        LOGIN, 
        SEND_ALL = 7, 
        LOGOUT = 8, 
        EXIT = 9 };

    std::string currentUser;
    std::vector<std::string>to;
    int choise;    
	int socket_file_descriptor, connection, bytes_read;
	struct sockaddr_in serveraddress, client;
    ChatCommandData ccd;
};

