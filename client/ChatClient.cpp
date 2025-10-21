#include "ChatClient.h"
#include <limits>

//CCD
void ChatClient::ChatCommandData::showData()
{
			
			if(!cmd.empty())
				std::cout << "CMD: " << cmd << std::endl;
			
				if(!log.empty())
				std::cout << "Log: " << log << std::endl;

			if(!login.empty())
				std::cout << "Login: " << login << std::endl;
			
			if(!password.empty())
				std::cout << "Password: " << password << std::endl;
			
			if(!to.empty())
				std::cout << "To: " << to << std::endl;
			
			if(!from.empty())
				std::cout << "From: " << from << std::endl;
			
			if(!textMessage.empty())
				std::cout << "TextMessage: " << textMessage << std::endl;
}

void ChatClient::ChatCommandData::DataClear()
{
	cmd.clear();
	log.clear();
	login.clear();
	password.clear();
	to.clear();
	from.clear();
	textMessage.clear();
}

//Constructors
ChatClient::ChatClient() : socket_file_descriptor(-1), connection(-1), bytes_read(-1) { }

ChatClient::~ChatClient()
{
		if(socket_file_descriptor < 0)
		{
			close(socket_file_descriptor);
			socket_file_descriptor = -1;
			connection = -1;
			bytes_read = -1;
		}
}
//Socket
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

bool ChatClient::sendData()
{
	char buf[MESSAGE_LENGTH];
	outputDataHandler(buf);
	ssize_t n = send(socket_file_descriptor, buf, MESSAGE_LENGTH, 0);
	if(n < 0)
		return false;
	
	//ccd.showData();
	ccd.DataClear();

	return true;
}

bool ChatClient::recvData()
{
	char buf[MESSAGE_LENGTH];
	int n = recv(socket_file_descriptor, buf, sizeof(buf),0);
	if (n <= 0) 
	{
		std::cout << "Recv failed\n";
		return false;
	}
	inputDataHandler(buf, n);
	//ccd.DataClear();
	return true;
}
//Chat logic
bool ChatClient::AuthUser()
{
	ccd.cmd = "AUTH_USER";
	std::cout << "\n\t/ * * Авторизация * */ \n" << "Введите логин: "; std::cin >> ccd.login;
	std::cout << "Введите пароль: "; std::cin >> ccd.password;
	sendData();
	recvData();
	if(ccd.log == "1")
	{
		currentUser = ccd.from = ccd.login;
		return true;
	}
	

	
	std::cout << "\nОшибка авторизации (неверный логин или  пароль)\n";
	return false;
}

bool ChatClient::userRegister()
{
	ccd.cmd = "ADD_USER";
	std::cout << "\t/ * * Регистрация нового пользователя * */ \n" << "Придумайте логин: "; std::cin >> ccd.login;
	std::cin.ignore();
	std::cout << "Придумайте пароль: "; std::getline(std::cin, ccd.password);
	sendData();
	recvData();
	if(ccd.log == "0")
	{
		system("clear");
		std::cout << "\nИмя занято! Повторите!" << std::endl;
		return false;
	}
				//регистрация пользователя
	system("pause");
	system("clear");
	std::cout << "Регистрация успешна!" << std::endl;
	return true;
}

void ChatClient::inputDataHandler(char* ch1, int n)
	{
		//CMD:LOG:LOGIN:PASSWORD:TO:FROM:TEXTMESSAGE
		int count = 0;
		char sp = ':';

		for (int i = 0; i < n; i++)
		{
			if(ch1[i] == sp && count < 6)
			{
				count++;
				continue;
			}
			if(count == 0)
				ccd.cmd.push_back(ch1[i]);
			if(count == 1)
				ccd.log.push_back(ch1[i]);
			if(count == 2)
				ccd.login.push_back(ch1[i]);
			if(count == 3)
				ccd.password.push_back(ch1[i]);
			if(count == 4)
				ccd.to.push_back(ch1[i]);
			if (count == 5)
				ccd.from.push_back(ch1[i]);
			if(count == 6)
				ccd.textMessage.push_back(ch1[i]);
		}
		
	}

void ChatClient::outputDataHandler(char* ch1)
{
	//CMD:LOG:LOGIN:PASSWORD:TO:FROM:TEXTMESSAGE
	bzero(ch1, MESSAGE_LENGTH);
	char sp = ':';
	std::string fullData = ccd.cmd + sp + ccd.log + sp + ccd.login + sp + ccd.password + sp + ccd.to + sp + ccd.from + sp + ccd.textMessage;
	strcpy(ch1, fullData.c_str());
	ch1[fullData.size()] = '\0';

}

void ChatClient::listUser()
{
	while(true) 
	{
		recvData();
		to.push_back(ccd.to);
		//std::cout << ccd.to << std::endl;
		std::cout << ccd.cmd << std::endl;
		if(ccd.cmd == "CMD_STOP")
			break;
	}
	std::cout << "Call Stop\n";
}

void ChatClient::mainLoop()
{
	if(!SetupConnection())
	{
		std::cout << "Error:Setup connection\n";
		return;
	}

    while (choise != EXIT)
	{
		std::cout << "\n\t****Консольный чат****\n" << 
						REGISTER << ".Регистрация\n" << 
						LOGIN << ".Вход\n" << 
						EXIT << ".Выход\n" << 
						"Введите команду : ";

		std::cin >> choise;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
			switch (choise)
			{
				//Регистрация
			case REGISTER:
				userRegister();
			break;

			//Авторизация
			case LOGIN:

				//Сессия пользователя
				if (AuthUser())
				{
					
					//ccd.login = ccd.from;
					while (choise != LOGOUT)
					{
						
						system("clear");
						std::cout << "\nЗдравствуйте, " << currentUser << "!\n" << "Выберите адресата или действие\n";

						listUser();

						std::cout << SEND_ALL << ".Отправить всем\n" << LOGOUT << ".Выход\n" << "\nВыберите команду: ";  std::cin >> choise;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

						if (choise == SEND_ALL)		//Рассылка
						{
							while (ccd.textMessage != "exit")
							{
								std::cin.ignore();
								std::cout << "Сообщение (для выхода введите exit): "; std::cin >> ccd.textMessage;
								//chat.sendAllMessage(login, text);
								//std::cout << login << " :" << text << std::endl;
							}
						}
						else if (choise == LOGOUT)	//Выход пользователя
						{
							break;
						}
						else						//Отправка сообщения пользователю
						{
							//reciever = chat.getContact(choise);
							//chat.displayAllMessages(login, reciever);
							while (ccd.textMessage != "exit")
							{
								std::cin.ignore();
								std::cout << "Сообщение (для выхода введите exit): "; std::cin >> ccd.textMessage;
								//std::cout << chat.sendMessage(login, reciever, text);
								//std::cout << login << " :" << text << std::endl;
							}
						
							system("pause");
							
						}
					}
				}
				break;
			case EXIT:		//Завершение работы программы
				break;
			default:
				std::cout << "Неверно выбрана команда" << std::endl;
				break;
			}
	 }
}
