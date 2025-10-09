all: Chat-server Chat-client

Chat-server: server/server.cpp
	g++ server/server.cpp -o Chat-server

Chat-client: client/client.cpp
	g++ client/client.cpp -o Chat-client