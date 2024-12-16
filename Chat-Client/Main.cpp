#include "SocketHandler.h"


int main()
{
    SocketHandler soc;
   soc.SetupConnection("5.53.20.189", 63462);

    return 0;
}