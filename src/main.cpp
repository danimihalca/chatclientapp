#include <iostream>
#include <memory>
#include <thread>

#include <ChatClient/ChatClient.hpp>
#include <ChatClient/IChatClientListener.hpp>

const char* ADDRESS = "192.168.0.3";

class PrintListener : public IChatClientListener
{
public:
    void onMessageReceived(const std::string& message)
    {
        std::cout << "MESSAGE RECEIVED: " << message << std::endl;
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
    void onLoginSuccessful()
    {
        std::cout << "LOGGED IN" << std::endl;
    }

    void onLoginFailed(const std::string& message)
    {
        std::cout << "LOGIN FAILED:" << message << std::endl;

    }

};


int main()
{
    std::unique_ptr<IChatClient> chatClient(new ChatClient());
    {
        std::shared_ptr<IChatClientListener> listener(new PrintListener());
        chatClient->addChatClientListener(listener);
    }
    chatClient->setServerProperties(ADDRESS, 9003);
    std::string message;
    while (true)
    {
        std::cin >> message;
        if (message == "l")
        {
            chatClient->login("user2", "pwd2");
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
        chatClient->sendMessage(message);
    }

    return 0;
}
