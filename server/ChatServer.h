#pragma once
#include "../Message.h"
#include "../DataExchangeProtocol.h"
//#include "User.h"
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

public:

	Chat();
	~Chat();
	//Inet Logic
	bool initSocket();
	int acceptClient();
	bool recvData(int client_fd, DataExchangeProtocol& dep);
	bool sendData(int client_fd, DataExchangeProtocol& dep);
	
	//Chat Logic
	//Добавить пользователя
	void addUser(DataExchangeProtocol& dep); 
	void addUser(const User& user); 
	//Авторизация пользователя
	bool loginUser(int client_fd, DataExchangeProtocol& dep);
	//Список пользователей
	//void listUsers(const std::string& name);
	void listUsers(int client_fd, DataExchangeProtocol& dep, std::string& userName);
	//Отправка сообщения
	bool recvMessageToServer(DataExchangeProtocol& dep);
	void sendMessageToClient(int client_fd, DataExchangeProtocol& dep);
	void sendAllMessageToClient(int client_fd, DataExchangeProtocol& dep);
	
	//Отправка сообщения всем
	void recvMessageFromAll(DataExchangeProtocol& dep);
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

