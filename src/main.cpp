#include <iostream>
#include <memory>
#include <thread>

#include <IChatClient.h>
#include <ChatClient.h>

int main()
{
    std::unique_ptr<IChatClient> chatClient( new ChatClient);
    chatClient->initialize();
    chatClient->connect("ws://192.168.0.3:9002");
    std::thread serviceThread(&IChatClient::startService, chatClient.get());

    std::string message;
    do
    {
        std::cin >> message;
        chatClient->sendMessage(message);
    }
    while (message != "close");
    chatClient->closeConnection();
    serviceThread.join();
    return 0;
}
