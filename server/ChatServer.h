#pragma once
#include "Message.h"
#include "User.h"
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <limits>
#include <iostream>
#include <strings.h>
#include <unistd.h>

#define MESSAGE_LENGTH 1024
#define PORT 63462

class Chat
{
public:
	Chat();
	~Chat();

	bool initSocket();
	int acceptClient();
	bool recvData(int& clientSock);
	bool sendData(int clientSock, char* buf, int length);
	void inputDataHandler(char* buf, int length);

	//Добавить пользователя
	bool addUser(const User& user); 
	//Авторизация пользователя
	bool loginUser(const std::string& login, const std::string& password);
	//Список пользователей
	void listUsers(const std::string& name);
	//Отправка сообщения
	bool sendMessage(const std::string& from, const std::string& to, const std::string& text);
	//Отправка сообщения всем
	void sendAllMessage(const std::string& from, const std::string& text);
	//Вывод сообшений
	void displayAllMessages(const std::string& from, const std::string& to) const;
	//Выбор адресата
	std::string getContact(const int index) const;
	//Проверка на совпадения логина и пароля
	bool validateUser(const std::string& name, const std::string& password) const;
	bool validateUser(const User& user) const;
	

	void mainLoop();

	
private:
	std::vector<User>_user;
	std::vector<Message<std::string>>_textMessages;

	struct sockaddr_in serveraddress;
    int socket_file_descriptor, bind_status, connection_status;
};

