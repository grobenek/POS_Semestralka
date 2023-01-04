//
// Created by Peter Szathmáry on 04/01/2023.
//

#include "MenuControl.h"

#include "iostream"

void  MenuControl::displayMainMenu()
{
    std::cout << "Main menu:" << std::endl;
    std::cout << "1. Start simulation" << std::endl;
    std::cout << "2. Configure simulation" << std::endl;
    std::cout << "3. Save simulation" << std::endl;
    std::cout << "4. Load simulation" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void  MenuControl::displayConfigureSimulation()
{
    std::cout << "Configure simulation: " << std::endl;
    std::cout << "1. Add ant" << std::endl;
    std::cout << "2. Remove ant" << std::endl;
    std::cout << "3. Change position of ant" << std::endl;
    std::cout << "4. Generate random colors" << std::endl;
    std::cout << "5. Change color of Policko" << std::endl;
    std::cout << "6. Delete svet" << std::endl;
    std::cout << "0. Exit to Main menu" << std::endl;
}

void MenuControl::displaySaveSimulation()
{
    std::cout << "Save simulation:" << std::endl;
    std::cout << "Save localy" << std::endl;
    std::cout << "Save on server" << std::endl;
}

void MenuControl::displayLoadSimulation()
{
    std::cout << "Load simulation:" << std::endl;
    std::cout << "Load from this computer" << std::endl;
    std::cout << "Load from remote server" << std::endl;
}
