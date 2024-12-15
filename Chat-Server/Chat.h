#pragma once
#include <iostream>
#include "User.h"
#include "Message.h"
#include <vector>
#include "Socket.h"

class Chat
{
public:
    Chat() = default;
    ~Chat();
    bool addUser(const User& user);
    bool authUser();
    void sendMessage();
    
private:
std::vector<User>_user;
std::vector<Message<std::string>>_message;
std::vector<SocketHandler>_connection;
};