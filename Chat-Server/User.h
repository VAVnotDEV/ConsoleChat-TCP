#pragma once
#include <iostream>
#include <string>

class User
{
public:
    User() = default;
    User(std::string login, std::string password);
    ~User();
    
    std::string getPassword() const;
    std::string getLogin() const;

    void setLogin(std::string login);
    void setPassword(std::string password);
private:
std::string _login;
std::string _password;
};