#include "ChatClient.h"
#include <limits>


//Constructors
ChatClient::ChatClient() : _socket_file_descriptor(-1), _connection(-1), _bytes_read(-1) { }

ChatClient::~ChatClient()
{
	if(_socket_file_descriptor >= 0)
	{
		close(_socket_file_descriptor);
		_socket_file_descriptor = -1;
		_connection = -1;
		_bytes_read = -1;
	}
}
//Socket
bool ChatClient::SetupConnection()
{
	_socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if(_socket_file_descriptor == -1)
	{
		perror("Socket creation failed failed");  
		return false;
	}

	_serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	_serveraddress.sin_port = htons(PORT);
	_serveraddress.sin_family = AF_INET;

	_connection = connect(_socket_file_descriptor, (struct sockaddr*)&_serveraddress, sizeof(_serveraddress));
	
	if(_connection == -1)
	{
		perror("Connection with the server failed.!");
		return false;
	}

	return true;
}

bool ChatClient::sendData()
{
	char buf[MESSAGE_LENGTH];
	_dep.outputDataHandler(buf);
	ssize_t n = send(_socket_file_descriptor, buf, sizeof(buf), 0);
	if(n < 0)
		return false;
	
	//ccd.DataClear();

	return true;
}

bool ChatClient::recvData()
{
	char buf[MESSAGE_LENGTH];
	int n = recv(_socket_file_descriptor, buf, sizeof(buf),0);
	if (n <= 0) 
	{
		std::cout << "Recv failed\n";
		return false;
	}
	_dep.DataClear();
	_dep.inputDataHandler(buf, n);
	
	return true;
}
//Chat logic
bool ChatClient::AuthUser()
{
	_dep.cmd = _currentCMD = "AUTH_USER";

	std::cout << "\n\t/ * * Авторизация * */ \n" << "Введите логин: "; std::cin >> _dep.login;
	std::cout << "Введите пароль: "; std::cin >> _dep.password;
	_currentUser = _dep.login;
	_dep.showData();
	sendData();
	recvData();

	if(_dep.log == "ok")
	{
		// if(bGetListUsers)
		// {
			_dep.login = _currentUser;
			//bGetListUsers = false;
			getListUser();
			recvAllMessageFrom();
		//}
		return true;
	}
	
	std::cout << "\nОшибка авторизации (неверный логин или  пароль)\n";
	return false;
}

bool ChatClient::userRegister()
{
	_dep.cmd = "ADD_USER";
	std::cout << "\t/ * * Регистрация нового пользователя * */ \n" << "Придумайте логин: "; std::cin >> _dep.login;
	std::cin.ignore();
	std::cout << "Придумайте пароль: "; std::getline(std::cin, _dep.password);
	sendData();
	recvData();
	if(_dep.log == "0")
	{
		system("clear");
		std::cout << "\nИмя занято! Повторите! " << _dep.log << std::endl;
		return false;
	}
				//регистрация пользователя
	system("pause");
	system("clear");
	std::cout << "Регистрация успешна!" << std::endl;
	return true;
}

void ChatClient::getListUser()
{
	while(_dep.cmd != "CMD_STOP")
	{
		recvData();
		_to.push_back(_dep.to);
	}
}

void ChatClient::showListUser()
{
	if(!_to.empty())
		for (int i = 0; i < _to.size() - 1; i++)
			std::cout << i << "." << _to.at(i) << std::endl;
}

void ChatClient::sendMessage()
{
	_currentCMD = "SEND_MESSAGE";
	while (true)
	{
		//std::cin.ignore();
		std::cout << "Сообщение (для выхода введите exit) \n" << _currentUser << ": "; std::cin >> _dep.textMessage;
		_dep.cmd = _currentCMD;
		
		if(_dep.textMessage == "exit")
		{
			break;
		}
			else
		{
			//std::cout << currentUser << ": " << ccd.textMessage << std::endl;
			sendData();
			_dep.textMessage.clear();
		}
	}
	
}
void ChatClient::recvMessageFrom()
{
	_currentCMD = "RECV_MESSAGE";
	_dep.to = _currentUser;
	_dep.cmd = _currentCMD;
	sendData();
	recvData();
	_messages.emplace_back(_dep.from, _dep.to, _dep.textMessage);
	std::cout << _dep.from << ": " << _dep.textMessage << std::endl; 

}

void ChatClient::recvAllMessageFrom()
{
	_currentCMD = "RECV_MESSAGE";
	_dep.to = _currentUser;
	_dep.cmd = _currentCMD;
	sendData();
	
	while(_dep.cmd != "END")
	{	
		recvData();
		_messages.emplace_back(_dep.from, _dep.to, _dep.textMessage);
		//std::cout << ccd.from << ": " << ccd.textMessage << std::endl; 
	}



}

void ChatClient::showAllMessages()
{		
	if(!_messages.empty())
		for(const Message<std::string>& m : _messages)
		std::cout << m.getFrom() << ": " << m.getMessage() << std::endl;
}
void ChatClient::resetState()
{
	_currentCMD.clear();
	_currentUser.clear();
	_to.clear();
	_bGetListUsers = true;
	_dep.DataClear();
	_messages.clear();
	_dep.cmd = "EXIT";
}
void ChatClient::mainLoop()
{
	if(!SetupConnection())
		return;

    while (_choise != EXIT)
	{
		_dep.DataClear();
		std::cout << "\n\t****Консольный чат****\n" << 
						REGISTER << ".Регистрация\n" << 
						LOGIN << ".Вход\n" << 
						EXIT << ".Выход\n" << 
						"Введите команду : ";

		std::cin >> _choise;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		switch (_choise)
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
				while (_choise != LOGOUT)
				{	
					//sendData();
					//system("clear");
					std::cout << "\nЗдравствуйте, " << _currentUser << "!\n" << "Выберите контакт или действие\n";
				
					showListUser();
					showAllMessages();

					std::cout << SEND_ALL << ".Отправить всем\n" << 
								LOGOUT << ".Выход\n" << 
								"\nВыберите команду: ";  
								
					std::cin >> _choise;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					if (_choise == SEND_ALL)		//Рассылка
					{
						_dep.to.clear();
						_currentCMD = "SEND_ALL";
						sendMessage();
						continue;
					}
					else if (_choise == LOGOUT)	//Выход пользователя
					{
						resetState();
						sendData();
						_dep.DataClear();
						break;
					}
					else
					{						
						std::string currentTo = _to.at(_choise);
						_dep.to = currentTo;
						//recvAllMessageFrom();
						//sendMessage();
						
						continue;
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
}
