//
// Created by ghost on 5. 1. 2023.
//

#include <cstring>
#include <iostream>
#include "Server.h"

Server::Server(const int maxClients, int port) : maxClients(maxClients), port(port), numberOfConnectedClients(0) {
    this->thread_clients = new std::thread*[this->maxClients];
    this->clients = new Client*[this->maxClients];
    this->newsockfds = new int[this->maxClients];
}

void Server::createServer() {
    bzero((char*)&serv_addr, sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = INADDR_ANY;
    this->serv_addr.sin_port = this->port;

    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0)
    {
        perror("Error creating socket");
        exit(1);
    }

    if (bind(this->sockfd, (struct sockaddr*)&serv_addr, sizeof(this->serv_addr)) < 0)
    {
        perror("Error binding socket address");
        exit(2);
    }
    // TODO this->maxClients netusim ci to su fakt maxClients
    listen(this->sockfd, this->maxClients);
    this->cli_len = sizeof(this->cli_addr);

    // TODO joiny a close vymysliet + odoslana sprava, ale neprijata a nezobrazena
}

bool Server::clientConnect() {
    this->newsockfds[this->numberOfConnectedClients] = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
    if (this->newsockfds[this->numberOfConnectedClients] < 0)
    {
        perror("ERROR on accept");
        return false;
    }
    std::cout << "Client connected with ID: " << this->numberOfConnectedClients << std::endl;
    this->clients[this->numberOfConnectedClients] = new Client(
                                                    this->numberOfConnectedClients,
                                                    this->newsockfds[this->numberOfConnectedClients],
                                                    this->thread_clients[this->numberOfConnectedClients]);
    this->thread_clients[this->numberOfConnectedClients] = this->clients[this->numberOfConnectedClients]->createThread();

    this->thread_clients[this->numberOfConnectedClients]->join();
    this->numberOfConnectedClients++;
    return true;
}

Server::~Server() {
    for (int i = 0; i < this->maxClients; ++i) {
        delete this->clients[i];
        delete this->thread_clients[i];
    }

    delete this->clients;
    delete this->thread_clients;
    delete this->newsockfds;
}
