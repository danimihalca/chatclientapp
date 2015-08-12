#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <ChatClient/ChatClient.hpp>
#include <ChatClient/IChatClientListener.hpp>

const char* ADDRESS = "192.168.0.3";
std::vector<Contact> myContacts;

class PrintListener : public IChatClientListener
{
public:
	void onMessageReceived(const Message& message)
    {
        std::cout << "MESSAGE RECEIVED FROM "<<message.getSenderId()<<":"<< message.getMessageText() << std::endl;
    }

    void onConnected()
    {
        std::cout << "CONNECTED" << std::endl;
    }

    void onConnectionError()
    {
        std::cout << "CONNECTION ERROR" << std::endl;
    }

    void onDisconnected()
    {
        std::cout << "DISCONNECTED" << std::endl;
    }
	void onLoginSuccessful(const UserDetails& userDetails)
    {
		std::cout << "LOGGED IN as " << userDetails.getFirstName()<< std::endl;
    }

    void onLoginFailed(const std::string& message)
    {
        std::cout << "LOGIN FAILED:" << message << std::endl;

    }
	void onContactsReceived(const std::vector<Contact>& contacts){
		for (auto c : contacts)
		{
			std::cout <<"RECEIVED:"<< c.getId() << " " << c.getUserName() << std::endl;
			myContacts.push_back(c);
		}
	}
	void onContactStateChanged(int contactId, CONTACT_STATE state)
	{

	}


	void onRemovedByContact(int contactId)
	{
		std::cout << "REMOVED BY " << contactId << std::endl;

	}
	void onAddContactResponse(const std::string& userName, bool accepted)
	{
		std::cout << userName << " has accepted:" << (accepted ? "true" : "false") << std::endl;
	}
	bool onAddingByContact(const std::string& requester)
	{
		std::cout << "REQUEST BY " << requester << "Accept? [y/n]" << std::endl;
		std::string m;
		std::cin >> m;
		if (m == "y")
		{
			std::cout << "ACCEPTING" << std::endl;
			return true;
		}
		std::cout << "DECLINING " << std::endl;
		return false;

	}
};


int main()
{
    std::unique_ptr<IChatClient> chatClient(new ChatClient());
        std::unique_ptr<IChatClientListener> listener(new PrintListener());
        chatClient->addListener(listener.get());
   
    chatClient->connect(ADDRESS, 9003);
    std::string message;
    while (true)
    {
        std::cin >> message;
        if (message == "l")
        {
			std::string username;
			std::string password;
			std::cout << "U:";
			std::cin >> username;
			std::cout << "P:";
			std::cin >> password; 
			UserCredentials cred(username,password);
			chatClient->login(cred);
            continue;
        }
        if (message == "d")
        {
            chatClient->disconnect();
            continue;
        }
        if (message == "x")
        {
            break;
        }
		if (message == "m")
		{
			int contactId;
			std::cout << "ContactID:";
			std::cin >> contactId;
			std::string message;
			std::cout << "M:";
			std::cin >> message;
			chatClient->sendMessage(contactId,message);
		}
		if (message == "lc")
		{
			for (auto c : myContacts)
			{
				std::cout << c.getId() << " " << c.getUserName() << std::endl;
			}
		}
		if (message == "r")
		{
			int contactId;
			std::cout << "ContactID:";
			std::cin >> contactId;
			chatClient->removeContact(contactId);
		}
		if (message == "a")
		{
			std::string username;
			std::cout << "U:";
			std::cin >> username;
			chatClient->addContact(username);
		}
    }

    return 0;
}
