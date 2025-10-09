#pragma once
#include "Message.h"
#include "User.h"
#include <vector>


class Chat
{
public:
	Chat() = default;
	~Chat() = default;

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
	bool validateUser(const std::string& name, const std::string& password) const;
	bool validateUser(const User& user) const;

	
private:
	std::vector<User>_user;
	std::vector<Message<std::string>>_textMessages;

};

//Выход за границы массива
class Bad_Range : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "ERROR: index out of range";
	}
};