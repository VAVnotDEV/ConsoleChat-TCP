all: Server-Chat/Server Client-Chat/Client

Client-Chat/Client: Client-Chat/Main-client.cpp
		g++ -o Client-Chat/Client Client-Chat/Main-client.cpp Client-Chat/ClientSock.cpp

Server-Chat/Server: Server-Chat/Main-Server.cpp
		g++ -o Server-Chat/Server Server-Chat/Main-Server.cpp Server-Chat/User.cpp Server-Chat/Message.cpp Server-Chat/ServerSock.cpp