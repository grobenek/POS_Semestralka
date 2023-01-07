////
//// Created by ghost on 5. 1. 2023.
////
//
//#include <iostream>
//#include <netdb.h>
//#include <cstring>
//#include <unistd.h>
//#include "Client.h"
//
//Client::Client(int id, int newsockfd, std::thread* thread) : id(id), newsockfd(newsockfd) {
//    this->thread = thread;
//}
//
//std::thread* Client::createThread() {
//    return new std::thread(&Client::clientRun, this);
//}
//
//void Client::clientRun() {
//    std::cout << "Client %d" << this->id << "Running" << std::endl;
//}
//
//Client::~Client() {
//    delete thread;
//}
//
//bool Client::createConnection(int port, std::string ip) {
//    this->server = gethostbyname(ip.c_str());
//
//    if (this->server == nullptr) {
//        std::cout << "Can't find this server." << std::endl;
//        return false;
//    }
//
//    bzero((char*)&serv_addr, sizeof(this->serv_addr));
//    this->serv_addr.sin_family = AF_INET;
//    bcopy(
//            (char*)server->h_addr,
//            (char*)&serv_addr.sin_addr.s_addr,
//            this->server->h_length
//    );
//    this->serv_addr.sin_port = port;
//
//    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (this->sockfd < 0) {
//        std::cout << "Can't create socket." << std::endl;
//        return false;
//    }
//
//    if(connect(this->sockfd, (struct sockaddr*)&serv_addr, sizeof(this->serv_addr)) < 0) {
//        std::cout << "An error occurred while establishing the connection!" << std::endl;
//        return false;
//    }
//
//    this->send("Message");
//
//    return true;
//}
//
//void Client::send(std::string message) {
//    bzero(this->buffer,256);
//    strcpy(this->buffer, message.c_str());
//    this->n = write(this->sockfd, this->buffer, strlen(this->buffer));
//    if (this->n < 0)
//    {
//        perror("Error writing to socket");
//    }
//}


#include <iostream>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include "Client.h"
#include <thread>

void Client::clientRun()
{
    // Run the client's communication with the server.
    // This could involve sending messages to the server, receiving messages from the server, and possibly doing some other processing.
    std::cout << "Client: my main method is running" << std::endl;

//    while (true)
//    {
//        std::string a;
//        std::cin >> a;
//        send(a);
//        std::cout << readMessageFromServer() << std::endl;
//    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    send("end");

    readMessageFromServer();
}

std::string Client::readMessageFromServer()
{
    bzero(this->buffer, 256);
    this->n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        exit(4);
    }
    std::string bufferInString = buffer;
    return bufferInString;
}

bool Client::createConnection(int port, const std::string& ip)
{
    // Establish a connection with a server.
    this->server = gethostbyname(ip.c_str());

    if (this->server == nullptr)
    {
        std::cout << "Can't find this server." << std::endl;
        return false;
    }

    bzero((char*) &serv_addr, sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    bcopy(
            (char*) server->h_addr,
            (char*) &serv_addr.sin_addr.s_addr,
            this->server->h_length
    );
    this->serv_addr.sin_port = port;

    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0)
    {
        std::cout << "Can't create socket." << std::endl;
        return false;
    }

    if (connect(this->sockfd, (struct sockaddr*) &serv_addr, sizeof(this->serv_addr)) < 0)
    {
        std::cout << "An error occurred while establishing the connection!" << std::endl;
        return false;
    }

    this->clientRun();

    return true;
}

void Client::send(const std::string& message)
{
    // Send a message to the server.
    bzero(this->buffer, 256);
    strcpy(this->buffer, message.c_str());
    this->n = write(this->sockfd, this->buffer, strlen(this->buffer));
    if (this->n < 0)
    {
        perror("Error writing to socket");
    }
}

int Client::getId() const
{
    return id;
}

void Client::setId(int id)
{
    Client::id = id;
}

int Client::getSockfd() const
{
    return sockfd;
}

Client::Client()
= default;
