//
// Created by ghost on 5. 1. 2023.
//

#ifndef MRAVEC_SERVER_H
#define MRAVEC_SERVER_H

#include <unistd.h>
#include <thread>
#include <mutex>
#include <netinet/in.h>
#include <vector>
#include "../client/Client.h"

class Server {
private:
    std::mutex mutex;
    int sockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    std::thread thread_server;
    std::thread** thread_clients;
    Client** clients;
    int* newsockfds;
    int numberOfConnectedClients;

    const int maxClients;
    const int port;
public:
    Server(int maxClients, int port);

    virtual ~Server();

    void createServer();

    bool clientConnect();
};


#endif //MRAVEC_SERVER_H
