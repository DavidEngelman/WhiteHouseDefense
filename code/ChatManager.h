class ChatManager {

private:
	ChatUI chatUI;

public:
	void getMessages();

	void sendMessageToServer(int message);

	void getNewMessagesFromServer();
};
