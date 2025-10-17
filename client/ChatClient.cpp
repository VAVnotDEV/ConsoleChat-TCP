#include "ChatClient.h"

ChatClient::ChatClient() : socket_file_descriptor(-1), connection(-1), bytes_read(-1) { }

ChatClient::~ChatClient()
{
		if(socket_file_descriptor > 0)
		{
			close(socket_file_descriptor);
			socket_file_descriptor = -1;
			connection = -1;
			bytes_read = -1;
		}
}

bool ChatClient::SetupConnection()
{
	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

		if(socket_file_descriptor == -1)
		{
			perror("Socket creation failed failed");  
			return false;
		}

		serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
		serveraddress.sin_port = htons(PORT);
		serveraddress.sin_family = AF_INET;

		connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
		
		if(connection == -1)
		{
        	perror("Connection with the server failed.!");
        	return false;
		}

		return true;
}

void ChatClient::sendData(std::string& s)
{
	std::cout << "Sender\n";
   ssize_t n = send(socket_file_descriptor, s.c_str(), s.size(), 0);
   if(n <= 0)
   {
	std::cout << "Send Failed\n";
	return;
   }
   std::cout << "Send OK\n";
}

void ChatClient::recvData()
{
	char buf[MESSAGE_LENGTH];
	int n = recv(socket_file_descriptor, buf, MESSAGE_LENGTH - 1, 0);
	std::cout << buf << std::endl;
}
bool ChatClient::AuthUser()
{
	return true;
}

bool ChatClient::Register()
{
	return true;
}

void ChatClient::mainLoop()
{
	if(!SetupConnection())
	{
		std::cout << "Error:Setup connection\n";
		return;
	}
	std::string m;

	while(true)
	{
	std::cout << "Enter message: "; 
	std::cin >> m;
	sendData(m);
	}

    // while (choise != EXIT)
	// {
	// 	std::cout << "\n\t****Консольный чат****\n" << REGISTER << ".Регистрация\n" << LOGIN << ".Вход\n"  << EXIT << ".Выход\n" << "Введите команду : ";

	// 	std::cin >> choise;
	// 	std::cin.clear();
	// 	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	// 		switch (choise)
	// 		{
	// 			//Регистрация
	// 		case REGISTER:
	// 		{
	// 			std::cout << "\t/ * * Регистрация нового пользователя * */ \n" << "Придумайте логин: "; //std::cin >> login;
	// 			std::cin.ignore();
	// 			std::cout << "Придумайте пароль: "; //std::getline(std::cin, password);

    //                      //регистрация пользователя
	// 			system("pause");
	// 			system("cls");
	// 		}
	// 		break;

	// 		//Авторизация
	// 		case LOGIN:
	// 			//std::cout << "\n\t/ * * Авторизация * */ \n" << "Введите логин: "; std::cin >> login;
	// 			//std::cout << "Введите пароль: "; std::cin >> password;

	// 			//Сессия пользователя
	// 			if (1)
	// 			{
	// 				while (choise != LOGOUT)
	// 				{
	// 					std::string text, reciever;
	// 					system("cls");
	// 					//std::cout << "\nЗдравствуйте, " << login << "!\n" << "Выберите адресата или действие\n";

	// 					//chat.listUsers(login);

	// 					std::cout << SEND_ALL << ".Отправить всем\n" << LOGOUT << ".Выход\n" << "\nВыберите команду: ";  std::cin >> choise;
	// 					std::cin.clear();
	// 					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// 					if (choise == SEND_ALL)		//Рассылка
	// 					{
	// 						while (text != "exit")
	// 						{
	// 							std::cin.ignore();
	// 							std::cout << "Сообщение (для выхода введите exit): "; std::cin >> text;
	// 							//chat.sendAllMessage(login, text);
	// 							//std::cout << login << " :" << text << std::endl;
	// 						}
	// 					}
	// 					else if (choise == LOGOUT)	//Выход пользователя
	// 					{
	// 						break;
	// 					}
	// 					else						//Отправка сообщения пользователю
	// 					{
	// 							//reciever = chat.getContact(choise);
	// 							//chat.displayAllMessages(login, reciever);
	// 							while (text != "exit")
	// 							{
	// 								std::cin.ignore();
	// 								std::cout << "Сообщение (для выхода введите exit): "; std::cin >> text;
	// 								//std::cout << chat.sendMessage(login, reciever, text);
	// 								//std::cout << login << " :" << text << std::endl;
	// 							}
							
	// 							system("pause");
							
	// 					}
	// 				}
	// 			}
	// 			break;
	// 		case EXIT:		//Завершение работы программы
	// 			break;
	// 		default:
	// 			std::cout << "Неверно выбрана команда" << std::endl;
	// 			break;
	// 		}
	// }
}
