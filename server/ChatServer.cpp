#include "ChatServer.h"

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
bool Chat::addUser(const User& user)
{
	for (const User& u : _user)
		if (!validateUser(user))
		{
			std::cout << "Имя занято, повторите" << std::endl;

			return false;
		}

	std::cout << "Пользователь успешно добавлен" << std::endl;

	_user.push_back(user);

	return true;
}
//Авторизация
bool Chat::loginUser(const std::string& name, const std::string& password) 
{
	if (validateUser(name, password))
		return true;

	std::cout << "\nОшибка авторизации (неверный логин или  пароль)\n";
	return false;
}
//Список контактов
void Chat::listUsers(const std::string& name) 
{
	std::cout << "\nСписок контактов: " << std::endl;
	int count = 0;
	for(const User& u : _user)
	{
		if (u.getName() == name)
			continue;
		count++;
		std::cout << count << " - " << u.getName() << std::endl;
	}
	std::cout << std::endl;
}

//Отправка конкретному пользователю
bool Chat::sendMessage(const std::string& from, const std::string& to, const std::string& text)
{
	if (text == "exit")
	{
		return false;
	}

	for (const User& u : _user)
	{
		if (u.getName() == to)
		{
			_textMessages.emplace_back(from, to, text);
			return true;
		}
	}
	std::cout << "Собщение не отправлено, адресат не найден" << std::endl;

	return false;
}
//Рассылка
void Chat::sendAllMessage(const std::string& from, const std::string& text)
{
	if (text == "exit")
		return;
	
	for (const User& u : _user)
	{
		if (u.getName() == from)
			continue;

		_textMessages.emplace_back(from, u.getName(), text);
	}
}

void Chat::displayAllMessages(const std::string& from, const std::string& to) const
{
	for(const Message<std::string>& m : _textMessages)
		if ((from == m.getFrom() && to == m.getTo()) || (from == m.getTo() && to == m.getFrom()))
			std::cout << "От: " << m.getFrom() << " Сообщение: " << m.getMessage() << std::endl;
}

std::string Chat::getContact(const int index) const
{
	return _user.at(index).getName();
}

bool Chat::validateUser(const std::string& name, const std::string& password) const
{
	for ( const User& u : _user)
			if (u.getName() == name && u.getPassword() == password)
				return true;
			
	return false;
}

bool Chat::validateUser(const User& user) const
{
	for (const User& u : _user)
		if (u.getName() == user.getName())
			return false;

	return true;
}

bool Chat::recvData(int& clientSock)
{
	char buf[MESSAGE_LENGTH];
	int n = recv(clientSock, buf, sizeof(buf),0);
	if (n <= 0) 
	{
		std::cout << "Recv failed\n";
		return false;
	}
	//передать дальше в обработчик
	std::cout << buf;
	//inputDataHandler(buf, n);
	return true;
}

bool Chat::sendData(int clientSock, char* buf, int length)
{
	ssize_t n = send(clientSock, buf, length, 0);
	return true;
}

void Chat::inputDataHandler(char* buf, int length)
{
	//std::cout << "CMD: " << cmd << " Login: " << login << " Password: " << password << std::endl;   
}

void Chat::mainLoop()
{
	if(!initSocket())
	{
		std::cout << "Error: initSocket\n";
		return;
	}

	char buf[MESSAGE_LENGTH];
 	std::string cmd, login, password, to, recieve, message;
	
	while(true)
	{
		int client_fd = acceptClient();
		if (client_fd < 0) continue;

		while(true)
		{
			int n = recv(client_fd, buf, MESSAGE_LENGTH - 1, 0);
			if(n <=0)
			{
				std::cout << "RECV Failed\n"; 
				close(client_fd);
				break;
			}
			buf[n] = '\0';

			int count = 0;
			//обработка буфера
			for (int i = 0; i < n; ++i)
			{
				if(buf[i] == ':')
				{
					count++;
					continue;
				} 
				else if(buf[i] == '\r' || buf[i] == '\n' || buf[i] == '\0')
				{
					continue;
				}       
				else if(count == 0)
					cmd.push_back(buf[i]);
					
				else if(count ==1)
					login.push_back(buf[i]);
				
				else if(count ==2)
					password.push_back(buf[i]);     
			}

				if (cmd == "add_user")
				{
					std::cout << "REGISTER\n";   
					// User* u = new User(login, password);
					// addUser(*u);
					cmd.clear();
					continue;
				}
				else if (cmd == "CMD_LOGIN")
				{
					std::cout << "Login\n";
					//if(loginUser(login, password))
					continue;

				}
				else if(cmd == "CMD_SEND_DATA")
				{	
					std::cout << "Send\n";
					//отправка
					continue;
				}
				else if (cmd == "CMD_RECV_DATA")
				{
					//получение
					continue;
				}
				else 
				continue;

			
			std::cout << cmd << " " << login << " " << password << std::endl;
			
		}
	}
}
	

	




