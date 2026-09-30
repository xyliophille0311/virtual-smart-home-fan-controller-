#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0)
    {
        std::cout << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    if (connect(clientSocket,
                (struct sockaddr*)&serverAddress,
                sizeof(serverAddress)) < 0)
    {
        std::cout << "Connection failed\n";
        close(clientSocket);
        return 1;
    }

    int temperature;

    std::cout << "Enter temperature: ";
    std::cin >> temperature;

    std::string message = std::to_string(temperature);

    send(clientSocket, message.c_str(), message.length(), 0);

    std::cout << "Temperature sent to server.\n";

    close(clientSocket);

    return 0;
}
