#ifndef CLIENT_H
#define CLIENT_H

#include <netdb.h>
#include <cstring>
#include <unistd.h>

class Client
{
private:
    int sockfd;
    struct sockaddr_in serv_addr{};
    struct hostent* server{};
    char buffer[256]{};
    int n{};
    int id{};


public:
    explicit Client(int newsockfd) : sockfd(newsockfd)
    {};

    Client();

    void clientRun();

    bool createConnection(int port, const std::string& ip);

    void send(const std::string& message);

    std::string readMessageFromServer();
};

#endif // CLIENT_H

