#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

constexpr int g_port = 8080;
constexpr int g_bufferSize = 1024;

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[g_bufferSize] = {0};

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("Socket creation failed");
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serverAddr.sin_port = htons(g_port);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) 
    {
        perror("Connection failed");
        return -1;
    }

    std::cout << "Connected to server" << std::endl;

    while (true) 
    {
        std::cout << "Enter message: ";
        std::cin.getline(buffer, g_bufferSize);

        if (send(clientSocket, buffer, strlen(buffer), 0) < 0)
        {
            perror("Send failed");
            break;
        }

        int bytesRead = recv(clientSocket, buffer, g_bufferSize, 0);
        if (bytesRead < 0) 
        {
            perror("Receive failed");
            break;
        } 
        else if (bytesRead == 0) 
        {
            std::cout << "Server disconnected" << std::endl;
            break;
        }

        std::cout << "Server acknowledgment: " << buffer << std::endl;

        memset(buffer, 0, g_bufferSize);
    }

    close(clientSocket);

    return 0;
}