//
// Created by ghost on 5. 1. 2023.
//

#ifndef MRAVEC_SERVER_H
#define MRAVEC_SERVER_H

#include <unistd.h>
#include <thread>
#include <mutex>
#include <netinet/in.h>
#include <map>
#include "../client/Client.h"

class Server
{
private:
    void communicationWithClientThreadFunction(int clientId, int pSockfd);

    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int port;
    int maxClients;
    int lastHighestId = 0;
    std::map<int, Client*> clients;
public:
    Server(int maxClients, int port);

    void createServer();

    void acceptClient();

    void serverRun();

    void send(const std::string& message, int pSockfd);

    void SendListOfAllFilesToDownload(int clientId, int pSockfd);

    void deleteClient(int clientId);

    void sendTextFile(const std::string& fileName, int clientSocket, int clientId);

    std::string readMessageFromClient(int pSockfd);
};


#endif //MRAVEC_SERVER_H
