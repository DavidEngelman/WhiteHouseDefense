all: server
	
server: code/Server.cpp
	g++ code/Server.cpp -o Server