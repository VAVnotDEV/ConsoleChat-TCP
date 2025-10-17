all: Chat-server Chat-client

Chat-server: server/Main.cpp
	g++ -o server-chat server/Main.cpp server/Message.h server/User.cpp server/ChatServer.cpp
Chat-client: client/Main.cpp
	g++ -o client-chat client/Main.cpp client/ChatClient.cpp