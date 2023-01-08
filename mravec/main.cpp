#include <iostream>
#include <cstring>
#include "plocha/pole/Pole.h"
#include "svet/Svet.h"
#include "mravec/inverzny/MravecInverzny.h"
#include "command/MenuControl.h"
#include "connections/server/Server.h"

#define LOAD_DIRECTORY_NAME "saves/"

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "server") == 0) {
        Server server(10, 10219);
        server.createServer();
        server.serverRun();
    } else if (strcmp(argv[1], "client") == 0) {
        Svet* svet = nullptr;
        std::cout << "Press 'enter' to start the application." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while (true)
        {
            int choice = MenuControl::readInput(0, 6, MenuControl::getMainMenuString());

            switch (choice)
            {
                case 1:
                    svet = MenuControl::runSimulation(svet);
                    break;
                case 2:
                    choice = MenuControl::readInput(0, 7, MenuControl::getConfigureSimulationString());
                    switch (choice)
                    {
                        case 1:
                            MenuControl::addAnt(svet);
                            break;
                        case 2:
                            MenuControl::deleteAllAnts(svet);
                            break;
                        case 3:
                            MenuControl::changePositionOfAnt(svet);
                            break;
                        case 4:
                            MenuControl::generateColorsForSvet(svet);
                            break;
                        case 5:
                            MenuControl::changeColorOfPolicko(svet);
                            break;
                        case 6:
                            svet = MenuControl::deleteSvet(svet);
                            break;
                        case 0:
                            break;
                    }
                    break;
                case 3:
                    choice = MenuControl::readInput(1, 2, MenuControl::displaySaveSimulation());
                    switch (choice) {
                        case 1:
                            MenuControl::saveSvetLocaly(svet);
                            break;
                        case 2:
                            Client client;
                            int port = MenuControl::readInput(10000, 10500, "Write port: ");
                            std::cout << "Write ip or server name: " << std::endl;
                            std::cout << ">>";
                            std::string server;
                            std::cin >> server;
                            client.createConnection(port, server);
                            std::cout << "Write upload for upload file to server, 'end' for disconnect" << std::endl;
                            break;
                    }

                    break;
                case 4:
                    choice = MenuControl::readInput(1, 2, MenuControl::displayLoadSimulation());
                    switch (choice) {
                        case 1:
                            svet = MenuControl::loadSvetLocaly(svet, LOAD_DIRECTORY_NAME);
                            break;
                        case 2:
                            Client client;
                            int port = MenuControl::readInput(10000, 10500, "Write port: ");
                            std::cout << "Write ip or server name: " << std::endl;
                            std::cout << ">>";
                            std::string server;
                            std::cin >> server;
                            client.createConnection(port, server);
                            std::cout << "Write 'download' for download file from server, 'end' for disconnect. " << std::endl;
                            break;
                    }
                    break;
                case 5:
                    MenuControl::printSvet(svet);
                    break;
                case 6:
                    svet = MenuControl::createSvet(svet);
                    break;
                case 0:
                    delete svet;
                    exit(0);
            }
        }
    }
}
