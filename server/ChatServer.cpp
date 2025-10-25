#include "ChatServer.h"

//CHAT-Inet
Chat::Chat() : socket_file_descriptor(-1), bind_status(-1), connection_status(-1) {}

Chat::~Chat()
{
	if(socket_file_descriptor != -1)
	close(socket_file_descriptor);
}

bool Chat::initSocket()
{
		socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

		if(socket_file_descriptor == -1)
		{
			perror("Socket creation failed");
			return false;
		}

		serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
		serveraddress.sin_port = htons(PORT);
		serveraddress.sin_family = AF_INET;

		//Привязка сокета
		bind_status = bind(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
		if(bind_status == -1)
		{
			perror("Socket binding status!");
			return false;
		}
		
		// Поставим сервер на прием данных 
		connection_status = listen(socket_file_descriptor, 5);
		
		if (connection_status == -1)
		{
    		std::cout << "Socket is unable to listen for new connections.!" << std::endl;
    		return false;
    	}  
		else  
		{
            std::cout << "Server is listening for new connection: " << std::endl;
        }
		
		return true;

}

int Chat::acceptClient()
{
		struct sockaddr_in client;
		socklen_t length = sizeof(client);
		
		int connection = accept(socket_file_descriptor, (struct sockaddr*)&client, &length);
		
		if(connection <= 0)  
		{
        	perror("Server is unable to accept the data from client.!");
        	return -1;
    	}

		std::cout << "Client accept\n";
		return connection;
}

bool Chat::recvData(int client_fd, DataExchangeProtocol& dep)
{
	char buf[MESSAGE_LENGTH];
	int n = recv(client_fd, buf, sizeof(buf),0);
	if (n <= 0) 
	{
		std::cout << "Disconnect\n";
		return false;
	}
	
	dep.DataClear();
	dep.inputDataHandler(buf, n);
	return true;
}
bool Chat::sendData(int client_fd, DataExchangeProtocol& dep)
{
	char buf[MESSAGE_LENGTH];
	dep.outputDataHandler(buf);
	ssize_t n = send(client_fd, buf, sizeof(buf), 0);
	if(n < 0)
		return false;
	//dep.DataClear();
	
	return true;
}
//Chat
void Chat::addUser(DataExchangeProtocol& dep)
{
	User u(dep.login, dep.password);
	std::cout << "Пользователь успешно добавлен" << std::endl;
	_user.push_back(u);
	dep.log = "1";
}
void Chat::addUser(const User& user)
{
	std::cout << "Пользователь успешно добавлен" << std::endl;
	_user.push_back(user);
}
//Авторизация
bool Chat::loginUser(int client_fd, DataExchangeProtocol& dep) 
{
	if (!validateAuthUser(dep.login, dep.password))
	{	
		std::cout << "\nServerLog:Ошибка авторизации (неверный логин или  пароль)\n";
		sendData(client_fd, dep);
	
		return false;
	}
	
	dep.log = "ok";
	std::string currentLogin = dep.login;
	
	sendData(client_fd, dep);
	
	listUsers(client_fd, dep, currentLogin);
	
	return true;
}

void Chat::listUsers(int client_fd, DataExchangeProtocol& dep, std::string& userName) 
{
	for(const User& u : _user)
	{
		if (u.getName() == userName)
			continue;

		dep.to = u.getName();
		sendData(client_fd, dep);
	}
	
	dep.cmd = "CMD_STOP";
	
	sendData(client_fd, dep);
}

//Получение сообщения на сервер
bool Chat::recvMessageToServer(DataExchangeProtocol& dep)
{
	for (const User& u : _user)
		if (u.getName() == dep.to)
		{
			_textMessages.emplace_back(dep.from, dep.to, dep.textMessage);
			std::cout << "Сообщение принято на сервер!\n";
			return true;
		}
		
	
	std::cout << "Собщение не принято на сервер" << std::endl;
	return false;
}

void Chat::sendAllMessageToClient(int client_fd, DataExchangeProtocol& dep)
{
	if(dep.textMessage == "exit")
		return;

	for(const Message<std::string>& m : _textMessages)
		if(dep.to == m.getTo())
		{
			dep.textMessage = m.getMessage();
			dep.from = m.getFrom();
			sendData(client_fd, dep);
			std::cout << "Сообщение отпрвлено клиенту\n";
			dep.showData();
		}

	sendData(client_fd, dep);
	
}

void Chat::sendMessageToClient(int client_fd, DataExchangeProtocol& dep)
{
	if(dep.textMessage == "exit")
		return;

	for(const Message<std::string>& m : _textMessages)
		if(dep.to == m.getTo() || dep.to == m.getFrom())
		{
			dep.textMessage = m.getMessage();
			dep.from = m.getFrom();
			sendData(client_fd, dep);
			std::cout << "Сообщение отпрвлено клиенту\n";
			dep.showData();
		}

	dep.DataClear();
	dep.cmd = "END";
	sendData(client_fd, dep);
	
}

//Рассылка
void Chat::recvMessageFromAll(DataExchangeProtocol& dep)
{	
	dep.showData();
	if(dep.textMessage == "exit")
		return;
	
	for (const User& u : _user)
	{
		if (u.getName() == dep.from)
			continue;
		
			_textMessages.emplace_back(dep.from, u.getName(), dep.textMessage);
	}
	dep.showData();
	std::cout << "Сообщение отправлено всем!" << std::endl;
}

// void Chat::displayAllMessages(const std::string& from, const std::string& to) const
// {
// 	for(const Message<std::string>& m : _textMessages)
// 		if ((from == m.getFrom() && to == m.getTo()) || (from == m.getTo() && to == m.getFrom()))
// 			std::cout << "От: " << m.getFrom() << " Сообщение: " << m.getMessage() << std::endl;
// }

bool Chat::validateAuthUser(const std::string& name, const std::string& password) const
{
	for ( const User& u : _user)
			if (u.getName() == name && u.getPassword() == password)
				return true;
			
	return false;
}

bool Chat::validateAddUser(std::string& login, std::string& log) const
{
	std::cout << login << std::endl;
	for (const User& u : _user)
		if (u.getName() == login)
		{
			log = "0";
			std::cout << "Имя занято\n";
			return false;
		}
		
	return true;
}

void Chat::mainLoop()
{
	User u1("VAV", "qwe");
	User u2("DEN", "qwe");
	User u3("Tom", "qwe");

	addUser(u1);
	addUser(u2);
	addUser(u3);

	_textMessages.emplace_back("DEN", "VAV", "Привет, как дела?");
	_textMessages.emplace_back("VAV", "DEN", "Отлично. Твои как?");
	_textMessages.emplace_back("DEN", "VAV", "Тоже хорошо, чем занят?");
	_textMessages.emplace_back("VAV", "DEN", "Пытаюсь не ёбнуться!");

	if(!initSocket())
		return;

	DataExchangeProtocol dep;
	bool bAuth = false;
	while(true)
	{
		int client_fd = acceptClient();
		if (client_fd < 0) break;

		while(true)
		{
			if(!recvData(client_fd, dep))			
					break;
			dep.showData();
			//Регистрация
			if (dep.cmd == "ADD_USER")
			{  
				if(validateAddUser(dep.login, dep.log))
				{
					std::cout << "AddUser\n";
					addUser(dep);
				}
				sendData(client_fd, dep);			
				continue;
			}
			
			//Авторизация
			else if (dep.cmd == "AUTH_USER")
			{
				loginUser(client_fd, dep);

				continue;
			}
			//Получение сообщения от клиента
			else if(dep.cmd == "SEND_MESSAGE")
			{	
				recvMessageToServer(dep);
				continue;
			}
			//Отправка
			else if (dep.cmd == "RECV_MESSAGE")
			{
				sendMessageToClient(client_fd, dep);
				continue;
			}
			else if(dep.cmd == "SEND_ALL")
			{
				recvMessageFromAll(dep);
				//sendData(client_fd, dep);
				continue;
			}
			else if (dep.cmd == "EXIT")
			{
				dep.DataClear();
				continue;;
			}
			
		}
		
		break;
	}
}

	




