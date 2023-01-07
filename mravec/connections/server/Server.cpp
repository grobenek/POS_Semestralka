//
// Created by ghost on 5. 1. 2023.
//

#include <cstring>
#include <iostream>
#include "Server.h"

Server::Server(const int maxClients, int port) : maxClients(maxClients), port(port)
{}

void Server::createServer()
{
    bzero((char*) &serv_addr, sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = INADDR_ANY;
    this->serv_addr.sin_port = this->port;

    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0)
    {
        perror("Error creating socket");
        exit(1);
    }

    if (bind(this->sockfd, (struct sockaddr*) &serv_addr, sizeof(this->serv_addr)) < 0)
    {
        perror("Error binding socket address");
        exit(2);
    }

    listen(this->sockfd, this->maxClients);
    std::cout << "Server is ready and listening!" << std::endl;
}

void Server::serverRun()
{
    while (true)
    {
        if (this->clients.size() >= this->maxClients)
        {
            continue;
        }
        this->acceptClient();
        std::thread clientThread(&Server::communicationWithClientThreadFunction, this, this->lastHighestId, newsockfd);
        clientThread.detach();
    }
}

void Server::acceptClient()
{
    this->newsockfd = accept(this->sockfd, (struct sockaddr*) &cli_addr, &cli_len);
    if (this->newsockfd < 0)
    {
        perror("Error accepting client connection");
        exit(3);
    }
    this->lastHighestId++;
    this->clients.insert(std::make_pair(this->lastHighestId, new Client(this->newsockfd)));
}

void Server::communicationWithClientThreadFunction(int clientId, int pSockfd)
{
    std::cout << "Communicating with client #" << clientId << std::endl;

    //TODO Toto je metoda kde SERVER posliela a prijima spravy s konkretnym klientom

    char buffer[256];
    while (true)
    {
        bzero(buffer, 256);
        int n = read(pSockfd, buffer, 255);
        if (n < 0)
        {
            perror("Error reading from socket");
            exit(4);
        }
        std::string bufferInString = buffer;

        if (strcmp(bufferInString.c_str(), "end") == 0)
        {
            send("Ending conversation!", pSockfd);
            std::cout << "Ending coversation with client #" << clientId << std::endl;

            auto clientToRemoveIterator = clients.find(clientId);
            if (clientToRemoveIterator != clients.end())
            {
                auto clientToRemove = clientToRemoveIterator->second;
                delete clientToRemove;
                clients.erase(clientToRemoveIterator);
            }
            break;
        }

        std::cout << "Message from client #" << clientId << " : " << bufferInString << std::endl;
        send("I've got your message!", pSockfd);
    }
}

void Server::send(const std::string& message, int pSockfd)
{
    // Send a message to the client
    char buffer[256];
    bzero(buffer, 256);
    strcpy(buffer, message.c_str());
    int recievedBytes = write(pSockfd, buffer, strlen(buffer));
    if (recievedBytes < 0)
    {
        perror("Error writing to socket");
    }
}