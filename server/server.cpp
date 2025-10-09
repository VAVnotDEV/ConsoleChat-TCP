//#include "Chat.h"
#include <limits>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
//#include "socketHandlerServer.h"

#define MESSAGE_LENGTH 1024
#define PORT 63462


class SocketHandlerServer
{
public:
	SocketHandlerServer() = default;
	~SocketHandlerServer() = default;
	
    void SetupConnect()
	{
		socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

		serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
		serveraddress.sin_port = htons(PORT);
		serveraddress.sin_family = AF_INET;

		//Привязка сокета
		bind_status = bind(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
		
		// Поставим сервер на прием данных 
		connection_status = listen(socket_file_descriptor, 5);
		
		length = sizeof(client);
		connection = accept(socket_file_descriptor, (struct sockaddr*)&client, &length);
	}

    //void sendData(char* message [MESSAGE_LENGTH]);
    void recvData(char message[MESSAGE_LENGTH])
	{
	
		while(500)
		{
			bzero(message, MESSAGE_LENGTH);
			recv(connection,message, MESSAGE_LENGTH, 0);
			std::cout << message << std::endl;
			
		}
	}

private:
    struct sockaddr_in serveraddress, client;
    socklen_t length;
    int socket_file_descriptor, connection, bind_status, connection_status;
    

};

int main()
{
	SocketHandlerServer sc;
	sc.SetupConnect();
	char m[MESSAGE_LENGTH];
	sc.recvData(m);
	return 0;
}

// int main()
// {
// 	setlocale(LC_ALL, "");

// 	Chat chat;
// 	enum command { REGISTER = 1, LOGIN, SEND_ALL = 7, LOGOUT = 8, EXIT = 9 };
// 	auto choise = 0;
// 	std::string login, password;

// 	User u1{ "Ivan", "a" };
// 	User u2{ "Gleb", "b" };
// 	User u3{ "a", "a" };
// 	chat.addUser(u1);
// 	chat.addUser(u2);
// 	chat.addUser(u3);

	
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

// 				User newUser(login, password);
// 				chat.addUser(newUser);

// 				system("pause");
// 				system("cls");
// 			}
// 			break;

// 			//Авторизация
// 			case LOGIN:
// 				std::cout << "\n\t/ * * Авторизация * */ \n" << "Введите логин: "; std::cin >> login;
// 				std::cout << "Введите пароль: "; std::cin >> password;

// 				//Сессия пользователя
// 				if (chat.loginUser(login, password))
// 				{
// 					while (choise != LOGOUT)
// 					{
// 						std::string text, reciever;
// 						system("cls");
// 						std::cout << "\nЗдравствуйте, " << login << "!\n" << "Выберите адресата или действие\n";

// 						chat.listUsers(login);

// 						std::cout << SEND_ALL << ".Отправить всем\n" << LOGOUT << ".Выход\n" << "\nВыберите команду: ";  std::cin >> choise;
// 						std::cin.clear();
// 						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

// 						if (choise == SEND_ALL)		//Рассылка
// 						{
// 							while (text != "exit")
// 							{
// 								std::cin.ignore();
// 								std::cout << "Сообщение (для выхода введите exit): "; std::cin >> text;
// 								chat.sendAllMessage(login, text);
// 								std::cout << login << " :" << text << std::endl;
// 							}
// 						}
// 						else if (choise == LOGOUT)	//Выход пользователя
// 						{
// 							break;
// 						}
// 						else						//Отправка сообщения пользователю
// 						{
// 							try {
// 								reciever = chat.getContact(choise);
// 								chat.displayAllMessages(login, reciever);
// 								while (text != "exit")
// 								{
// 									std::cin.ignore();
// 									std::cout << "Сообщение (для выхода введите exit): "; std::cin >> text;
// 									std::cout << chat.sendMessage(login, reciever, text);
// 									std::cout << login << " :" << text << std::endl;
// 								}
// 							}
// 							catch (Bad_Range& r)
// 							{
// 								std::cout << r.what() << std::endl;
// 								system("pause");
// 							}
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
