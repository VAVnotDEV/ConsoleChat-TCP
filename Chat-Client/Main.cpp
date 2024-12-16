#include "SocketHandler.h"


int main()
{
    SocketHandler sock;
    sock.SetupConnection("5.53.20.189", 63462);
    return 0;
}