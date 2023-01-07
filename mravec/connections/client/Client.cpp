#include <iostream>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include "Client.h"
#include <thread>

void Client::clientRun()
{
    std::cout << "Client: my main method is running" << std::endl;

    //TODO Toto je metoda kde klient posliela a prijima spravy

    while (true)
    {
        std::string message;
        std::cin >> message;
        send(message);
        std::string messageFromServer = readMessageFromServer();
        std::cout << "Server: " << messageFromServer << std::endl;

        if (strcmp(message.c_str(), "end") == 0)
        {
            break;
        }
    }

    std::cout << "Client #" << this->id << " is disconnecting" << std::endl;
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
    bzero(this->buffer, 256);
    strcpy(this->buffer, message.c_str());
    this->n = write(this->sockfd, this->buffer, strlen(this->buffer));
    if (this->n < 0)
    {
        perror("Error writing to socket");
    }
}

Client::Client()
= default;
