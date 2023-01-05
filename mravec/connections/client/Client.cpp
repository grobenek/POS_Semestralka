//
// Created by ghost on 5. 1. 2023.
//

#include <iostream>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include "Client.h"

Client::Client(int id, int newsockfd, std::thread* thread) : id(id), newsockfd(newsockfd) {
    this->thread = thread;
}

std::thread* Client::createThread() {
    return new std::thread(&Client::clientRun, this);
}

void Client::clientRun() {
    std::cout << "Client %d" << this->id << "Running" << std::endl;
}

Client::~Client() {
    delete thread;
}

bool Client::createConnection(int port, std::string ip) {
    this->server = gethostbyname(ip.c_str());

    if (this->server == nullptr) {
        std::cout << "Can't find this server." << std::endl;
        return false;
    }

    bzero((char*)&serv_addr, sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            this->server->h_length
    );
    this->serv_addr.sin_port = port;

    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0) {
        std::cout << "Can't create socket." << std::endl;
        return false;
    }

    if(connect(this->sockfd, (struct sockaddr*)&serv_addr, sizeof(this->serv_addr)) < 0) {
        std::cout << "An error occurred while establishing the connection!" << std::endl;
        return false;
    }

    this->send("Message");

    return true;
}

void Client::send(std::string message) {
    bzero(this->buffer,256);
    strcpy(this->buffer, message.c_str());
    this->n = write(this->sockfd, this->buffer, strlen(this->buffer));
    if (this->n < 0)
    {
        perror("Error writing to socket");
    }
}
