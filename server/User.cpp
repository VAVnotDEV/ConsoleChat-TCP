#include "User.h"


//Конструкторы
User::User(const std::string& name,const std::string& password) : _name(name), _password(password) {};
User::User(const std::string& name) : _name(name) {};
User::User(const User& other) : _name(other._name), _password(other._password){}
User::User(User&& other) noexcept : _name(move(other._name)), _password(move(other._password)) {}

//Гетеры
std::string User::getName() const { return _name; }
std::string User::getPassword() const { return _password; }

//Сетеры
void User::setName(std::string& name) { _name = name; }
void User::setPassword(std::string& password) { _password = password; }

//Операторы
User& User::operator=(User& other)
{
	_name = other._name;
	_password = other._password;
	return *this;
}
User& User::operator=(User&& other) noexcept
{
	_name = move(other._name);
	_password = move(other._password);
	return *this;
}

