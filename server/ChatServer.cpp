#include "ChatServer.h"

//CCD
void Chat::ChatCommandData::DataClear()
{
	cmd.clear();
	log.clear();
	login.clear();
	password.clear();
	to.clear();
	from.clear();
	textMessage.clear();
}

void Chat::ChatCommandData::showData()
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

//CHAT
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

//Регистрация пользователя
void Chat::addUser(ChatCommandData& ccd)
{
	User u(ccd.login, ccd.password);
	std::cout << "Пользователь успешно добавлен" << std::endl;
	_user.push_back(u);
	ccd.log = "1";
}
void Chat::addUser(const User& user)
{
	std::cout << "Пользователь успешно добавлен" << std::endl;
	_user.push_back(user);
}
//Авторизация
bool Chat::loginUser(ChatCommandData& ccd) 
{
	if (validateAuthUser(ccd.login, ccd.password))
	{	ccd.log = "1";
		return true;
	}
	std::cout << "\nServerLog:Ошибка авторизации (неверный логин или  пароль)\n";
	
	ccd.log = "0";
	return false;

}

void Chat::listUsers(int clientSock, ChatCommandData& ccd) 
{
	for(const User& u : _user)
	{
		if (u.getName() == ccd.login)
			continue;

		ccd.to = u.getName();
		sendData(clientSock, ccd);
	}
	
	ccd.cmd = "CMD_STOP";
	
	sendData(clientSock, ccd);
}

//Получение сообщения на сервер
bool Chat::recvMessageToServer(ChatCommandData& ccd)
{
	for (const User& u : _user)
		if (u.getName() == ccd.to)
		{
			_textMessages.emplace_back(ccd.from, ccd.to, ccd.textMessage);
			std::cout << "Сообщение принято на сервер!\n";
			return true;
		}
		
	
	std::cout << "Собщение не принято на сервер" << std::endl;
	return false;
}

void Chat::sendMessageToClient(ChatCommandData& ccd)
{
	for(const Message<std::string>& m : _textMessages)
		if(ccd.to == m.getTo())
		{
			ccd.textMessage = m.getMessage();
			ccd.from = m.getFrom();
		}
	std::cout << "Сообщение отпрвлено клиенту\n";
}

//Рассылка
void Chat::recvMessageFromAll(ChatCommandData& ccd)
{		
	for (const User& u : _user)
	{
		if (u.getName() == ccd.from)
			continue;
		
			_textMessages.emplace_back(ccd.from, u.getName(), ccd.textMessage);
	}
	
	std::cout << "Сообщение отправлено всем!" << std::endl;
}

// void Chat::displayAllMessages(const std::string& from, const std::string& to) const
// {
// 	for(const Message<std::string>& m : _textMessages)
// 		if ((from == m.getFrom() && to == m.getTo()) || (from == m.getTo() && to == m.getFrom()))
// 			std::cout << "От: " << m.getFrom() << " Сообщение: " << m.getMessage() << std::endl;
// }

// std::string Chat::getContact(const int index) const
// {
// 	return _user.at(index).getName();
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

bool Chat::recvData(int clientSock, ChatCommandData& ccd)
{
	std::cout << "Call recvData" << std::endl; 
	char buf[MESSAGE_LENGTH];
	int n = recv(clientSock, buf, sizeof(buf),0);
	if (n <= 0) 
	{
		std::cout << "Disconnect\n";
		return false;
	}
	ccd.DataClear();
	inputDataHandler(buf, n, ccd);
	return true;
}

bool Chat::sendData(int clientSock, ChatCommandData& ccd)
{
	std::cout << "Call sendData" << std::endl; 
	char buf[MESSAGE_LENGTH];
	outputDataHandler(ccd, buf);
	ssize_t n = send(clientSock, buf, MESSAGE_LENGTH, 0);
	if(n < 0)
		return false;
	ccd.DataClear();
	
	return true;
}

void Chat::inputDataHandler(char* ch1, int n, ChatCommandData& ccd)
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

void Chat::outputDataHandler(ChatCommandData& ccd, char* ch1)
{
	//CMD:LOG:LOGIN:PASSWORD:TO:FROM:TEXTMESSAGE
	bzero(ch1, MESSAGE_LENGTH);
	char sp = ':';
	std::string fullData = ccd.cmd + sp + ccd.log + sp + ccd.login + sp + ccd.password + sp + ccd.to + sp + ccd.from + sp + ccd.textMessage;
	strcpy(ch1, fullData.c_str());
	ch1[fullData.size()] = '\0';
}

void Chat::mainLoop()
{
	User u1("VAV", "qwe");
	User u2("DEN", "qwe");
	User u3("Tom", "qwe");

	addUser(u1);
	addUser(u2);
	addUser(u3);

	_textMessages.emplace_back("DEN", "VAV", "seample Text message DEN to VAV");
	_textMessages.emplace_back("DEN", "VAV", "seample Text message DEN to VAV");

	if(!initSocket())
		return;

	ChatCommandData ccd;
	bool bSendListUsers = false;
	while(true)
	{
		int client_fd = acceptClient();
		if (client_fd < 0) continue;
		
		while(true)
		{
			if(!recvData(client_fd, ccd))
				break;
			std::cout << "Begin" << std::endl;
			ccd.showData();
			//Регистрация
			if (ccd.cmd == "ADD_USER")
			{  
				if(validateAddUser(ccd.login, ccd.log))
				{
					std::cout << "AddUser\n";
					addUser(ccd);
				}
				sendData(client_fd, ccd);			
				continue;
			}
			
			//Авторизация
			else if (ccd.cmd == "AUTH_USER")
			{
				bool bAuth = loginUser(ccd);
				sendData(client_fd, ccd);
				recvData(client_fd, ccd);

				if(bAuth)
					if(!bSendListUsers)
					{
						listUsers(client_fd, ccd);
						bSendListUsers = true;
					}
				continue;
			}
			//Получение сообщения от клиента
			else if(ccd.cmd == "SEND_MESSAGE")
			{	
				std::cout << "Send\n";
				recvMessageToServer(ccd);
				continue;
			}
			//Отправка
			else if (ccd.cmd == "RECV_MESSAGE")
			{
				//recvData(client_fd, ccd);
				sendMessageToClient(ccd);
				sendData(client_fd, ccd);
				continue;
			}
			else if(ccd.cmd == "RECV_ALL")
			{
				ccd.showData();
				recvMessageFromAll(ccd);
				sendData(client_fd, ccd);
				continue;
			}
			
		}
		
		break;
	}
}

	




