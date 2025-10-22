#pragma once
#include "Message.h"
#include "User.h"
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <limits>
#include <iostream>
#include <string.h>
#include <unistd.h>

#define MESSAGE_LENGTH 1024
#define PORT 63462



class Chat
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

	Chat();
	~Chat();
	//Inet Logic
	bool initSocket();
	int acceptClient();
	bool recvData(int clientSock, ChatCommandData& ccd);
	bool sendData(int clientSock, ChatCommandData& ccd);
	
	
	void inputDataHandler(char* ch1, int n, ChatCommandData& ccd);
	void outputDataHandler(ChatCommandData& ccd, char* ch1);
	
	//Chat Logic
	//Добавить пользователя
	void addUser(ChatCommandData& ccd); 
	void addUser(const User& user); 
	//Авторизация пользователя
	bool loginUser(ChatCommandData& ccd);
	//Список пользователей
	//void listUsers(const std::string& name);
	void listUsers(int clientSock, ChatCommandData& ccd);
	//Отправка сообщения
	bool recvMessageToServer(ChatCommandData& ccd);
	void sendMessageToClient(ChatCommandData& ccd);
	
	//Отправка сообщения всем
	void sendAllMessage(ChatCommandData& ccd);
	//Вывод сообшений
	void displayAllMessages(const std::string& from, const std::string& to) const;
	//Выбор адресата
	//std::string getContact(const int index) const;
	//Проверка на совпадения логина и пароля
	bool validateAuthUser(const std::string& name, const std::string& password) const;
	bool validateAddUser(std::string& login, std::string& log) const;
	
	void mainLoop();


	
private:

	std::vector<User>_user;
	std::vector<Message<std::string>>_textMessages;
	struct sockaddr_in serveraddress;
    int socket_file_descriptor, bind_status, connection_status;




};

