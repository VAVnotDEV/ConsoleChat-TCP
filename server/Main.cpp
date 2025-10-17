#include "ChatServer.h"


int main()
{
    Chat chat;
    chat.mainLoop();
}

// int main()
// {
//     Chat chat;
//     if(!chat.initSocket())
//         return 1;
//       int cs = chat.acceptClient();
//         while(true)
//         {
      
//        // if(cs < 0)  continue;

//         char m[MESSAGE_LENGTH];


//             std::cout << "\nWaiting recieve...\n";

//             int n = recv(cs, m, sizeof(m), 0);
//             if (n <= 0) std::cout << "Recv failed\n";
//           //  m[n] = '\0';
//             std::cout << m;
//         }

//     return 0;
// }

