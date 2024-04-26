
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#include "buffer.hpp"

constexpr int g_port = 8080;
constexpr int g_bufferSize = 1024;

int main() 
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("Socket creation failed");
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(g_port);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) 
    {
        perror("Bind failed");
        return -1;
    }

    if (listen(serverSocket, 5) < 0) 
    {
        perror("Listen failed");
        return -1;
    }

    std::cout << "Server listening on g_port " << g_port << std::endl;

    if ((newSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize)) < 0) {
        perror("Accept failed");
        return -1;
    }

    std::cout << "Client connected" << std::endl;

    CircularBuffer buffer(g_bufferSize);

    while (true) 
    {
        char recvBuffer[g_bufferSize] = {0};
        int bytesRead = recv(newSocket, recvBuffer, g_bufferSize, 0);
        if (bytesRead < 0)
        {
            perror("Receive failed");
            break;
        } 
        else if (bytesRead == 0)
        {
            std::cout << "Client disconnected" << std::endl;
            break;
        }

        buffer.write(recvBuffer, bytesRead);

        const char *ackMsg = "Message received";
        if (send(newSocket, ackMsg, strlen(ackMsg), 0) < 0) 
        {
            perror("Send failed");
            break;
        }

        char processBuffer[g_bufferSize];
        int processedBytes = buffer.read(processBuffer, g_bufferSize);
        if (processedBytes > 0) 
        {
            std::cout << "Processed message: " << processBuffer << std::endl;
        }
    }

    close(newSocket);
    close(serverSocket);

    return 0;
}