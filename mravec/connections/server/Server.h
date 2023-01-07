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
    char buffer[256];
    std::map<int, Client*> clients;
public:
    Server(int maxClients, int port);

    void createServer();

    void acceptClient();

    void serverRun();

    void send(const std::string& message, int newsockfwd);
};


#endif //MRAVEC_SERVER_H