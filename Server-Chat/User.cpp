#include "User.h"

User::User(std::string login, std::string password) : _login(login), _password(password){}
User::~User(){}

std::string User::getLogin() const { return _login; }
std::string User::getPassword() const { return _password; }

void User::setLogin(std::string login) { _login = login; }
void User::setPassword(std::string password) { _password = password; }
