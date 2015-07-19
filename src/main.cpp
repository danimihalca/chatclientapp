#include <iostream>
#include <memory>
#include <thread>

#include <ChatClient/ChatClient.h>
#include <ChatClient/IChatClientListener.h>

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

    void onDisconnected()
    {
        std::cout << "DISCONNECTED" << std::endl;
    }
};


int main()
{
    std::unique_ptr<IChatClient> chatClient(new ChatClient());
    {
        std::shared_ptr<IChatClientListener> listener(new PrintListener());
        chatClient->addChatClientListener(listener);
    }

    std::string message;
    while (true)
    {
        std::cin >> message;
        if (message == "c")
        {
            chatClient->connect(ADDRESS, 9003);
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
