#include <iostream>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include "Client.h"

void Client::clientRun()
{
    std::cout << "Client: my main method is running" << std::endl;

//    std::thread clientThread(&Client::sendTestConnectionMesssage, this);

    //TODO Toto je metoda kde klient posliela a prijima spravy

    while (true)
    {
//        pthread_mutex_lock(&this->mutex);
//        if (this->connectionLost)
//        {
//            pthread_mutex_unlock(&this->mutex);
//            break;
//        }
//        pthread_mutex_unlock(&this->mutex);
//        if (!clientThread.joinable())
//        {
//            std::cout << "Connection to server lost!" << std::endl;
//            break;
//        }

        std::cout << "Write message: " << std::endl;
        std::string message;
        std::getline(std::cin, message);
        send(message);
        std::string messageFromServer = readMessageFromServer();

        if (strcmp(message.c_str(), "end") == 0)
        {
            break;
        }

        if (strcmp(messageFromServer.c_str(), "download") == 0)
        {
            message = "";
            std::cout << "Write file name: " << std::endl;
            std::cin >> message;
            send(message);
            this->readMessageFromServer();
            this->readFileFromServer("skuska.txt");
            continue;
        }

        if (strcmp(messageFromServer.c_str(), "upload") == 0)
        {
            this->sendFileToServer("saves/skuska.txt");
        }
        std::cout << "Server: " << messageFromServer << std::endl;
    }

//    pthread_mutex_lock(&this->mutex);
//    this->connectionLost = true;
//    pthread_mutex_unlock(&this->mutex);

//    clientThread.join();
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
    if (n == 0)
    {
        std::cerr << "Connection to server lost" << std::endl;
        throw std::runtime_error("Connection to server lost!");
    }
    std::string bufferInString = buffer;
    return bufferInString;
}

//std::string Client::readFileFromServer(const std::string& fileName)
//{
//    // Open the file to write the contents to
//    std::ofstream fileStream("saves/"+fileName);
//    if (!fileStream.is_open())
//    {
//        std::cerr << "Error opening file for writing" << std::endl;
//        return "";
//    }
//    char bufferForFile[256];
//    bzero(bufferForFile, 256);
//    while ((n = read(sockfd, bufferForFile, 256)) > 0) //TODO POZOR
//    {
//
//    }
//
//
//    std::cout << "Finished reading file from server" << std::endl;
//    return fileName;
//}
std::string Client::readFileFromServer(const std::string& fileName)
{
    // Open the file to write the contents to
    std::ofstream fileStream("saves/"+fileName);
    if (!fileStream.is_open())
    {
        std::cerr << "Error opening file for writing" << std::endl;
        return "";
    }

    // Read and save the file contents in chunks
    const size_t chunkSize = 256;
    char bufferForFile[chunkSize];
    this->n = read(sockfd, bufferForFile, chunkSize - 1);
    send("got it");
    if (this->n < 0)
    {
        perror("Error reading from socket");
        return "";
    }
    if (this->n == 0)
    {
        std::cerr << "Connection to server lost" << std::endl;
        throw std::runtime_error("Connection to server lost!");
    }
    while (this->n > 0)
    {
        std::string message = bufferForFile;
        fileStream << message << std::endl;
        bzero(bufferForFile, chunkSize);
        this->n = read(sockfd, bufferForFile, chunkSize - 1);
        std::string response = bufferForFile;
        if (strcmp(response.c_str(), "eof") == 0)
        {
            send("got it");
            break;
        }
        send("got it");
    }

    fileStream.close();
    std::cout << "Finished reading file from server" << std::endl;
    return fileName;
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
void Client::sendTestConnectionMesssage()
{
    while (true)
    {
        pthread_mutex_lock(&this->mutex);
        if (this->connectionLost)
        {
            pthread_mutex_unlock(&this->mutex);
            break;
        }
        pthread_mutex_unlock(&this->mutex);

        this->send("beep");
        try
        {
            this->readMessageFromServer();
        } catch (std::runtime_error& error)
        {
            pthread_mutex_lock(&this->mutex);
            this->connectionLost = true;
            pthread_mutex_unlock(&this->mutex);
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Client::sendFileToServer(const std::string& fileName)
{
    // Open the file
    std::cout << "Starting sending file to server" << std::endl;
    std::ifstream fileStream(fileName);
    if (!fileStream.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    char bufferForFile[256];
    bzero(bufferForFile, 256);

    while (fileStream.getline(bufferForFile, 256))
    {
        std::string message = bufferForFile;
        send(message);
        bzero(bufferForFile, 256);
        message = this->readMessageFromServer();
    }

    send("eof");

    fileStream.close();
    std::cout << "Finished sending file to server" << std::endl;
}

Client::Client()
= default;
