#include <iostream>
#include <memory>
#include <thread>

#include <IChatClient.h>
#include <ChatClient.h>

int main()
{
    std::unique_ptr<IChatClient> chatClient( new ChatClient);
    chatClient->initialize();
    chatClient->startService();

    std::string message;
    while (true)
    {
        std::cin >> message;
        if (message == "connect")
        {
            chatClient->connect("ws://192.168.0.3:9002");
            continue;
        }
        if (message == "disconnect")
        {
            chatClient->closeConnection();
            continue;
        }
        if (message == "close")
        {
            break;
        }
        chatClient->sendMessage(message);
    }

    return 0;
}
