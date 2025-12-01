#include "ChatClient.h"
#include <string.h>
#include <iostream>


int main()
{
    setlocale(LC_ALL, "");
#ifdef _WIN32
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed: " << wsaResult << std::endl;
        return 1;
    }
#endif
    {
        ChatClient chat;
        chat.mainLoop();
    }

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}



