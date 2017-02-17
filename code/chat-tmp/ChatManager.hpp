class ChatManager {

private:
	ChatUI chatUI;

public:
	void getMessages();

	void sendMessageToServer(Message message);

	Message[] getNewMessagesFromServer();
};
