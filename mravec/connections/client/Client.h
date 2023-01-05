//
// Created by ghost on 5. 1. 2023.
//

#ifndef MRAVEC_CLIENT_H
#define MRAVEC_CLIENT_H


#include <thread>
#include <netinet/in.h>

class Client {
private:
    int id;
    int newsockfd;
    int sockfd, n;
    std::thread* thread;
    char buffer[256];

    struct hostent* server;
    struct sockaddr_in serv_addr;
public:
    Client() = default;
    Client(int id, int newsockfd, std::thread* thread);

    virtual ~Client();

    std::thread * createThread();
    void clientRun();
    bool createConnection(int port, std::string ip);

private:
    void send(std::string message);
    void receive();
};


#endif //MRAVEC_CLIENT_H
