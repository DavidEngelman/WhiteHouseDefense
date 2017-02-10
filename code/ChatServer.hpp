class ChatServer : Server {


public:
	void getNewMessageRequests();

	void broadcast(Message message);
};
