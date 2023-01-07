////
//// Created by ghost on 5. 1. 2023.
////
//
//#ifndef MRAVEC_CLIENT_H
//#define MRAVEC_CLIENT_H
//
//
//#include <thread>
//#include <netinet/in.h>
//
//class Client {
//private:
//    int id;
//    int newsockfd;
//    int sockfd, n;
//    std::thread* thread;
//    char buffer[256];
//
//    struct hostent* server;
//    struct sockaddr_in serv_addr;
//public:
//    Client() = default;
//    Client(int id, int newsockfd, std::thread* thread);
//
//    virtual ~Client();
//
//    std::thread * createThread();
//    void clientRun();
//    bool createConnection(int port, std::string ip);
//
//private:
//    void send(std::string message);
//    void receive();
//};
//
//
//#endif //MRAVEC_CLIENT_H

#ifndef CLIENT_H
#define CLIENT_H

#include <netdb.h>
#include <cstring>
#include <unistd.h>

class Client
{
private:
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    char buffer[256];
    int n;
    int id;


public:
    Client(int newsockfd) : sockfd(newsockfd)
    {};

    Client();

    int getSockfd() const;

    void clientRun();

    bool createConnection(int port, const std::string& ip);

    void send(const std::string& message);

    int getId() const;

    void setId(int id);

    std::string readMessageFromServer();
};

#endif // CLIENT_H

