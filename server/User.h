#pragma once
#include <iostream>
#include <string>
#include <exception>


class User
{
private:
	std::string _name;
	std::string _password;

public:
	//Конструткоры, деструкторы
	User() = default;
	User(const std::string& name, const std::string& password);
	User(const std::string& name);

	User(const User& other);
	User(User&& other) noexcept;
	virtual ~User() = default;

	//Гетеры
	std::string getName() const;
	std::string getPassword() const;

	//Сетеры
	void setName(std::string& name);
	void setPassword(std::string& password);
	
	//Операторы
	User& operator=(User& other);
	User& operator=(User&& other) noexcept;

};