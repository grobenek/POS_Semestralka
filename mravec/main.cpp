#include <iostream>
#include <cstring>
#include "plocha/pole/Pole.h"
#include "svet/Svet.h"
#include "mravec/inverzny/MravecInverzny.h"
#include "command/MenuControl.h"
#include "connections/server/Server.h"

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "server") == 0) {
        Server server(10, 10137);
        server.createServer();
        server.serverRun();
    } else if (strcmp(argv[1], "client") == 0) {
        Client client;
        client.createConnection(10137, "localhost");
    }

//    Svet* svet = nullptr;
//    std::cout << "Press 'enter' to start the application." << std::endl;
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//    while (true)
//    {
//        int choice = MenuControl::readInput(0, 6, MenuControl::getMainMenuString());
//
//        switch (choice)
//        {
//            case 1:
//                svet = MenuControl::runSimulation(svet);
//                break;
//            case 2:
//                choice = MenuControl::readInput(0, 7, MenuControl::getConfigureSimulationString());
//                switch (choice)
//                {
//                    case 1:
//                        MenuControl::addAnt(svet);
//                        break;
//                    case 2:
//                        MenuControl::deleteAllAnts(svet);
//                        break;
//                    case 3:
//                        MenuControl::changePositionOfAnt(svet);
//                        break;
//                    case 4:
//                        MenuControl::generateColorsForSvet(svet);
//                        break;
//                    case 5:
//                        MenuControl::changeColorOfPolicko(svet);
//                        break;
//                    case 6:
//                        svet = MenuControl::deleteSvet(svet);
//                        break;
//                    case 0:
//                        break;
//                }
//                break;
//            case 3:
//                MenuControl::readInput(1, 2, MenuControl::displaySaveSimulation());
//                MenuControl::saveSvetLocaly(svet);
//                break;
//            case 4:
//                MenuControl::readInput(1, 2, MenuControl::displayLoadSimulation());
//                svet = MenuControl::loadSvetLocaly(svet);
//                break;
//            case 5:
//                MenuControl::printSvet(svet);
//                break;
//            case 6:
//                svet = MenuControl::createSvet(svet);
//                break;
//            case 0:
//                delete svet;
//                exit(0);
//        }
//    }
}
