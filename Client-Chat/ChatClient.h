#include "ClientSock.h"

class ChatClient
{
    public:
    void registerNewUser (std::string login, std::string password);
    bool userLogin(std::string login, std::string password);
    void session(int choose);
    
    private:
    ClientSock socket;
};