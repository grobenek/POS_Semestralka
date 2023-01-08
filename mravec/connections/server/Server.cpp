//
// Created by ghost on 5. 1. 2023.
//

#include <cstring>
#include <iostream>
#include <dirent.h>
#include <fstream>
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
    while (true)
    {
        std::string bufferInString = this->readMessageFromClient(pSockfd);

        if (strcmp(bufferInString.c_str(), "beep") == 0)
        {
            send("zijem", pSockfd);
            continue;
        }

        if (strcmp(bufferInString.c_str(), "printFilesToDownload") == 0)
        {
            SendListOfAllFilesToDownload(clientId, pSockfd);
            continue;
        }

        if (strcmp(bufferInString.c_str(), "end") == 0)
        {
            send("Ending conversation!", pSockfd);
            std::cout << "Ending coversation with client #" << clientId << std::endl;

            deleteClient(clientId);
            break;
        }

        if (strcmp(bufferInString.c_str(), "download") == 0)
        {
            send("download", pSockfd);
            std::string fileName = this->readMessageFromClient(pSockfd);
            send(fileName, pSockfd);
            fileName = "server/" + fileName;
            this->sendTextFile(fileName, pSockfd, clientId);
            continue;
        }

        if (strcmp(bufferInString.c_str(), "upload") == 0)
        {
            send("upload", pSockfd);
            this->readFileFromClient("skuska.txt", clientId, pSockfd);
        }

        std::cout << "Message from client #" << clientId << " : " << bufferInString << std::endl;
        send("I've got your message!", pSockfd);
    }
    std::cout << "Ending communication with client#" << clientId << std::endl;
}

std::string Server::readMessageFromClient(int pSockfd)
{
    char buffer[256];
    bzero(buffer, 256);
    int n = read(pSockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        exit(4);
    }
    if (n == 0)
    {
        std::cerr << "Connection to server lost" << std::endl;
        throw std::runtime_error("Connection to server lost!");
    }
    std::string bufferInString = buffer;
    return bufferInString;
}

void Server::deleteClient(int clientId)
{
    auto clientToRemoveIterator = clients.find(clientId);
    if (clientToRemoveIterator != clients.end())
    {
        auto clientToRemove = clientToRemoveIterator->second;
        delete clientToRemove;
        clients.erase(clientToRemoveIterator);
    }
}

void Server::SendListOfAllFilesToDownload(int clientId, int pSockfd)
{
    std::cout << "User #" << clientId << " requested list of all files" << std::endl;
    send("List of all save files:\n", pSockfd);
    if (auto dir = opendir("server/"))
    {
        while (auto f = readdir(dir))
        {
            if (strcmp(f->d_name, ".") == 0 || strcmp(f->d_name, "..") == 0)
            {
                continue;
            }
            send(f->d_name, pSockfd);
        }
        closedir(dir);
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

void Server::sendTextFile(const std::string& fileName, int clientSocket, int clientId)
{
    // Open the file
    std::cout << "Starting sending file to client#" << clientId << std::endl;
    std::ifstream fileStream(fileName);
    if (!fileStream.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    char bufferForFile[256];
    bzero(bufferForFile, 256);

    while (fileStream.getline(bufferForFile, 256))
    {
        std::string message = bufferForFile;
        send(message, clientSocket);
        bzero(bufferForFile, 256);
        message = this->readMessageFromClient(clientSocket);
    }

    send("eof", clientSocket);

    fileStream.close();
    std::cout << "Finished sending file to client#" << clientId << std::endl;
}

std::string Server::readFileFromClient(const std::string& fileName, int clientId, int clientSocket)
{
    // Open the file to write the contents to
    std::ofstream fileStream("server/"+fileName);
    if (!fileStream.is_open())
    {
        std::cerr << "Error opening file for writing" << std::endl;
        return "";
    }

    // Read and save the file contents in chunks
    const size_t chunkSize = 256;
    char bufferForFile[chunkSize];
    int n = read(clientSocket, bufferForFile, chunkSize - 1);
    send("got it", clientSocket);
    if (n < 0)
    {
        perror("Error reading from socket");
        return "";
    }
    if (n == 0)
    {
        std::cerr << "Connection to client lost" << std::endl;
        throw std::runtime_error("Connection to client lost!");
    }
    while (n > 0)
    {
        std::string message = bufferForFile;
        fileStream << message << std::endl;
        bzero(bufferForFile, chunkSize);
        n = read(clientSocket, bufferForFile, chunkSize - 1);
        std::string response = bufferForFile;
        if (strcmp(response.c_str(), "eof") == 0)
        {
            break;
        }
        send("got it", clientSocket);
    }

    fileStream.close();
    std::cout << "Finished reading file from client#" << clientId << std::endl;
    return fileName;
}
