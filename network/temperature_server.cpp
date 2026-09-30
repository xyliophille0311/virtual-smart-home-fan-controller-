#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
    {
        std::cout << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket,
             (struct sockaddr*)&serverAddress,
             sizeof(serverAddress)) < 0)
    {
        std::cout << "Bind failed\n";
        close(serverSocket);
        return 1;
    }

    listen(serverSocket, 5);

    std::cout << "Temperature server listening on port 8080...\n";

    // Continuously accept temperature readings
    while (true)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket < 0)
        {
            std::cout << "Accept failed\n";
            continue;
        }

        char buffer[100] = {0};

        read(clientSocket, buffer, sizeof(buffer));

        std::cout << "Received temperature: "
                  << buffer << " C\n";

        close(clientSocket);
    }

    close(serverSocket);

    return 0;
}