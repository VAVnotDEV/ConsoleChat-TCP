#include "Chat.h"


//Регистрация пользователя
bool Chat::addUser(const User& user)
{
	for (const User& u : _user)
		if (validateUser(user))
		{
			std::cout << "Имя занято, повторите" << std::endl;

			return false;
		}

	std::cout << "Пользователь успешно добавлен" << std::endl;

	_user.push_back(user);

	return true;
}
//Авторизация
bool Chat::loginUser(const std::string& name, const std::string& password) 
{
	if (validateUser(name, password))
		return true;

	std::cout << "\nОшибка авторизации (неверный логин или  пароль)\n";
	return false;
}
//Список контактов
void Chat::listUsers(const std::string& name) 
{
	std::cout << "\nСписок контактов: " << std::endl;
	int count = 0;
	for(const User& u : _user)
	{
		if (u.getName() == name)
			continue;
		count++;
		std::cout << count << " - " << u.getName() << std::endl;
	}
	std::cout << std::endl;
}
//Отправка конкретному пользователю
bool Chat::sendMessage(const std::string& from, const std::string& to, const std::string& text)
{
	if (text == "exit")
	{
		return false;
	}

	for (const User& u : _user)
	{
		if (u.getName() == to)
		{
			_textMessages.emplace_back(from, to, text);
			return true;
		}
	}
	std::cout << "Собщение не отправлено, адресат не найден" << std::endl;

	return false;
}
//Рассылка
void Chat::sendAllMessage(const std::string& from, const std::string& text)
{
	if (text == "exit")
		return;
	
	for (const User& u : _user)
	{
		if (u.getName() == from)
			continue;

		_textMessages.emplace_back(from, u.getName(), text);
	}
}

void Chat::displayAllMessages(const std::string& from, const std::string& to) const
{
	for(const Message<std::string>& m : _textMessages)
		if ((from == m.getFrom() && to == m.getTo()) || (from == m.getTo() && to == m.getFrom()))
			std::cout << "От: " << m.getFrom() << " Сообщение: " << m.getMessage() << std::endl;
}

std::string Chat::getContact(const int index) const
{
	return _user.at(index).getName();
}

bool Chat::validateUser(const std::string& name, const std::string& password) const
{
	for ( const User& u : _user)
			if (u.getName() == name && u.getPassword() == password)
				return true;
			
	return false;
}

bool Chat::validateUser(const User& user) const
{
	for (const User& u : _user)
		if (u.getName() == user.getName())
			return true;

	return false;
}
