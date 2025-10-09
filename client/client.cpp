#include <iostream>
#include <unistd.h>
#include <strings.h>
#include <limits>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //htonl ntohl

#define MESSAGE_LENGTH 1024
#define PORT 63462

class SocketHandlerClient
{
	public:
	SocketHandlerClient() = default;
	~SocketHandlerClient() = default;

	void SetupConnection()
	{
		socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

		serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
		serveraddress.sin_port = htons(PORT);
		serveraddress.sin_family = AF_INET;

		connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	}

	void sendMessage(const char message[MESSAGE_LENGTH])
	{
		
		send(socket_file_descriptor, message, MESSAGE_LENGTH, 0);

	}

	void recvMessage()
	{
			recv(socket_file_descriptor, message, sizeof(message), 0);
	}

private:
	int socket_file_descriptor, connection;
	struct sockaddr_in serveraddress, client;
	char message[MESSAGE_LENGTH];
};

int main()
{
	SocketHandlerClient sc;

	sc.SetupConnection();

	char m[MESSAGE_LENGTH];
	
		while (true)
		{
		std::cout << "\nEnter message: ";
		std::cin >> m;
		sc.sendMessage(m);
		std::cout << m << std::endl;
		bzero(m, MESSAGE_LENGTH);
		}

	return 0;
}


// int main()
// {
// 	setlocale(LC_ALL, "");

// 	enum command { REGISTER = 1, LOGIN, SEND_ALL = 7, LOGOUT = 8, EXIT = 9 };
// 	auto choise = 0;
// 	std::string login, password;
	
// 	while (choise != EXIT)
// 	{
// 		std::cout << "\n\t****Консольный чат****\n" << REGISTER << ".Регистрация\n" << LOGIN << ".Вход\n"  << EXIT << ".Выход\n" << "Введите команду : ";

// 		std::cin >> choise;
// 		std::cin.clear();
// 		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


// 			switch (choise)
// 			{
// 				//Регистрация
// 			case REGISTER:
// 			{
// 				std::cout << "\t/ * * Регистрация нового пользователя * */ \n" << "Придумайте логин: "; std::cin >> login;
// 				std::cin.ignore();
// 				std::cout << "Придумайте пароль: "; std::getline(std::cin, password);

//                          //регистрация пользователя
// 				system("pause");
// 				system("cls");
// 			}
// 			break;

// 			//Авторизация
// 			case LOGIN:
// 				std::cout << "\n\t/ * * Авторизация * */ \n" << "Введите логин: "; std::cin >> login;
// 				std::cout << "Введите пароль: "; std::cin >> password;

// 				//Сессия пользователя
// 				if (1)
// 				{
// 					while (choise != LOGOUT)
// 					{
// 						std::string text, reciever;
// 						system("cls");
// 						std::cout << "\nЗдравствуйте, " << login << "!\n" << "Выберите адресата или действие\n";

// 						//chat.listUsers(login);

// 						std::cout << SEND_ALL << ".Отправить всем\n" << LOGOUT << ".Выход\n" << "\nВыберите команду: ";  std::cin >> choise;
// 						std::cin.clear();
// 						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

// 						if (choise == SEND_ALL)		//Рассылка
// 						{
// 							while (text != "exit")
// 							{
// 								std::cin.ignore();
// 								std::cout << "Сообщение (для выхода введите exit): "; std::cin >> text;
// 								//chat.sendAllMessage(login, text);
// 								std::cout << login << " :" << text << std::endl;
// 							}
// 						}
// 						else if (choise == LOGOUT)	//Выход пользователя
// 						{
// 							break;
// 						}
// 						else						//Отправка сообщения пользователю
// 						{
// 								//reciever = chat.getContact(choise);
// 								//chat.displayAllMessages(login, reciever);
// 								while (text != "exit")
// 								{
// 									std::cin.ignore();
// 									std::cout << "Сообщение (для выхода введите exit): "; std::cin >> text;
// 									//std::cout << chat.sendMessage(login, reciever, text);
// 									std::cout << login << " :" << text << std::endl;
// 								}
							
// 								system("pause");
							
// 						}
// 					}
// 				}
// 				break;
// 			case EXIT:		//Завершение работы программы
// 				break;
// 			default:
// 				std::cout << "Неверно выбрана команда" << std::endl;
// 				break;
// 			}
// 	}

// 	return 0;
// }
