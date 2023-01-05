//
// Created by Peter Szathmáry on 04/01/2023.
//

#include <regex>
#include "MenuControl.h"

#include "iostream"
#include "../simulacia/Simulacia.h"
#include "../mravec/priamy/MravecPriamy.h"
#include "../mravec/inverzny/MravecInverzny.h"
#include "../file/upload/FileUpload.h"
#include "../file/download/FileDownload.h"

#define MAX_DIMENSION_SIZE 1000

#define MIN_DIMENSION_SIZE 3

std::string MenuControl::getMainMenuString()
{
    std::string menu = "Main menu:\n"
                       "1. Start simulation\n"
                       "2. Configure simulation\n"
                       "3. Save simulation\n"
                       "4. Load simulation\n"
                       "5. Print svet\n"
                       "6. Create svet\n"
                       "0. Exit";
    return menu;
}

std::string MenuControl::getConfigureSimulationString()
{
    std::string menu = "Configure simulation: \n"
                       "1. Add ant\n"
                       "2. Remove all ants\n"
                       "3. Change position of ant\n"
                       "4. Generate random colors\n"
                       "5. Change color of Policko\n"
                       "6. Delete svet\n"
                       "0. Exit to Main menu";
    return menu;
}

std::string MenuControl::displaySaveSimulation()
{
    std::string menu = "Save simulation:\n"
                       "1. Save localy\n"
                       "2. Save on remote server";

    return menu;
}

std::string MenuControl::displayLoadSimulation()
{
    std::string menu = "Load simulation:\n"
                       "1. Load from this computer\n"
                       "2. Save on remote server";

    return menu;
}

void MenuControl::addAnt(Svet* svet)
{
    if (svet == nullptr)
    {
        std::cout << "Svet is not generated yet! Generate one and try again!" << std::endl;
        return;
    }

    int input = readInput(1, 2, "Type of ant:\n1. Priamy\n2. Inverzny");

    int x, y, direction;
    mravec::Mravec* ant;
    switch (input)
    {
        case 1:
            x = readInput(0, svet->getWidth() - 1, "X coordinate of ant: ");
            y = readInput(0, svet->getHeight() - 1, "Y coordinate of ant: ");
            direction = readInput(1, 4, "Direction of ant:\n1. North\n2. East\n3. South\n4. West");
            ant = new mravec::MravecPriamy(x, y, static_cast<Smer>(direction - 1));
            svet->addAnt(ant);
            break;
        case 2:
            x = readInput(0, svet->getWidth() - 1, "X coordinate of ant: ");
            y = readInput(0, svet->getHeight() - 1, "Y coordinate of ant: ");
            direction = readInput(1, 4, "Direction of ant:\n1. North\n2. East\n3. South\n4. West");
            ant = new mravec::MravecInverzny(x, y, static_cast<Smer>(direction - 1));
            svet->addAnt(ant);
            break;
        default:
            std::cout << "Undefined input!" << std::endl;
            return;
    }
    std::cout << "Ant added to policko!" << std::endl;
}

int MenuControl::readInput(int minRange, int maxRange, const std::string& stringToPrint)
{
    int input;

    while (true)
    {
        std::cout << std::endl << stringToPrint << std::endl;
        std::cout << ">> ";
        std::cin >> input;

        if (!std::cin.fail() && input >= minRange && input <= maxRange)
        {
            break;
        } else
        {
            std::cout << "Invalid input. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return input;
}

void MenuControl::generateColorsForSvet(Svet* svet)
{
    if (svet == nullptr)
    {
        std::cout << "Svet is not generated yet! Generate one and try again!" << std::endl;
        return;
    }

    svet->generateRandomColors();

    std::cout << "Random colors have been generated!" << std::endl;
}

void MenuControl::deleteAllAnts(Svet* svet)
{
    if (svet == nullptr)
    {
        std::cout << "Svet is not generated yet! Generate one and try again!" << std::endl;
        return;
    }

    svet->deleteAllAnts();

    std::cout << "All ants have been deleted!" << std::endl;
}

void MenuControl::changePositionOfAnt(Svet* svet)
{
    if (svet == nullptr)
    {
        std::cout << "Svet is not generated yet! Generate one and try again!" << std::endl;
        return;
    }

    int x = MenuControl::readInput(0, svet->getWidth(), "X coordinate of Policko with ant: ");
    int y = MenuControl::readInput(0, svet->getHeight(), "Y coordinate of Policko with ant: ");

    auto* ant = svet->getPolicko(x, y)->getAnt(0);
    if (ant == nullptr)
    {
        std::cout << "No ant present on Policko x: " << x << " y: " << y << std::endl;
        return;
    }
    svet->getPolicko(x, y)->removeAnt(0);

    x = MenuControl::readInput(0, svet->getWidth(), "X coordinate of new Policko for ant: ");
    y = MenuControl::readInput(0, svet->getHeight(), "Y coordinate of new Policko for ant: ");

    ant->setRowPos(x);
    ant->setColumnPos(y);

    svet->getPolicko(x, y)->addAnt(ant);

    std::cout << "Ant has been added to Policko x: " << x << " y: " << y << std::endl;
}

void MenuControl::changeColorOfPolicko(Svet* svet)
{
    if (svet == nullptr)
    {
        std::cout << "Svet is not generated yet! Generate one and try again!" << std::endl;
        return;
    }

    int x = MenuControl::readInput(0, svet->getWidth(), "X coordinate of Policko: ");
    int y = MenuControl::readInput(0, svet->getHeight(), "Y coordinate of Policko: ");

    svet->getPolicko(x, y)->changeColor();

    std::cout << "Policko x: " << x << " y: " << y << " has been changed to " << svet->getColorOfPolicko(x, y)
              << " color" << std::endl;
}

Svet* MenuControl::deleteSvet(Svet* svet)
{
    int choice = MenuControl::readInput(1, 2, "Are you sure you want to delete svet?\n1. Yes\n2. No");

    if (choice == 2)
    {
        std::cout << "Deleting has been aborted!" << std::endl;
        return svet;
    }

    delete svet;
    svet = nullptr;
    std::cout << "Svet has been deleted!" << std::endl;
    return svet;
}

void MenuControl::saveSvetLocaly(Svet* svet)
{
    if (svet == nullptr)
    {
        std::cout << "Svet is not generated yet! Generate one and try again!" << std::endl;
        return;
    }

    std::string input;
    std::cin.ignore();

    while (true)
    {
        std::cout << "Enter file name you want to save Svet to: ";
        std::getline(std::cin, input);

        if (std::regex_match(input, std::regex("^[a-zA-Z0-9_]*(\\.txt)?$")))
        {
            break;
        }

        std::cout << std::endl << "File name can only contain letters and numbers. Try again!" << std::endl;
    }

    if (input.length() < 4 || input.substr(input.length() - 4) != ".txt")
    {
        input += ".txt";
    }

    FileUpload fileUpload(input);
    fileUpload.saveSvetIntoFile(*svet);

    std::cout << "Svet has been sucesfully saved into file with name " << input << std::endl;
}

Svet* MenuControl::loadSvetLocaly(Svet* svet)
{
    delete svet;

    std::string input;
    std::cin.ignore();

    while (true)
    {
        std::cout << "Enter file name you want to load Svet from: ";
        std::getline(std::cin, input);

        if (std::regex_match(input, std::regex("^[a-zA-Z0-9_]*(\\.txt)?$")))
        {
            break;
        }

        std::cout << std::endl << "File name can only contain letters and numbers. Try again!" << std::endl;
    }

    if (input.length() < 4 || input.substr(input.length() - 4) != ".txt")
    {
        input += ".txt";
    }

    FileDownload fileDownload;
    try
    {
        svet = fileDownload.createSvetFromFile(input);

        std::cout << "Svet has been succesfully loaded from file with name " << input << std::endl;

        return svet;
    } catch (std::runtime_error& e)
    {
        std::cout << "Svet couldn't be loaded from file with name " << input << std::endl;
        return nullptr;
    }
}

Svet* MenuControl::runSimulation(Svet* svet)
{
    if (svet == nullptr)
    {
        std::cout << "Svet is not created!" << std::endl << "Creating one now" << std::endl;
        svet = createSvet(nullptr);
    }

    int input = getNumberOfSteps();
    std::cout << "Simulation has started!" << std::endl;
    Simulacia simulacia(input, svet);
    svet->printSvet();
    std::cout << std::endl;
    simulacia.simulate();
    return svet;
}

int MenuControl::getNumberOfSteps()
{
    std::string input;
    std::cin.ignore();
    while (true)
    {
        std::cout << "Enter number of steps in simulation: ";
        std::getline(std::cin, input);

        if (std::regex_match(input, std::regex("\\d+")) && std::stoi(input) > 0)
        {
            break;
        }

        std::cout << "Input must be positive whole number greater than 0. Try again!" << std::endl;
    }
    return std::stoi(input);
}

Svet* MenuControl::createSvet(Svet* svet)
{
    if (svet != nullptr)
    {
        std::cout << "Deleting your current svet!" << std::endl;
        delete svet;
    }

    int width = readInput(MIN_DIMENSION_SIZE, MAX_DIMENSION_SIZE, "Width of Svet (3-1000): ");
    int height = readInput(MIN_DIMENSION_SIZE, MAX_DIMENSION_SIZE, "Height of Svet (3-1000): ");

    Pole* pole = new Pole(width, height);

    int numberOfAnts = readInput(1, MAX_DIMENSION_SIZE, "Number of ants (1-1000)");

    auto* ants = new std::vector<mravec::Mravec*>();

    for (int i = 0; i < numberOfAnts; ++i)
    {
        int input = readInput(1, 2, "Type of ant:\n1. Priamy\n2. Inverzny");

        mravec::Mravec* ant;
        switch (input)
        {
            case 1:
                ant = new mravec::MravecPriamy();
                ants->push_back(ant);
                break;
            case 2:
                ant = new mravec::MravecInverzny();
                ants->push_back(ant);
                break;
            default:
                std::cout << "Undefined input!" << std::endl;
                break;
        }
        std::cout << "Ant added!" << std::endl;
    }

    Svet* svetToReturn = new Svet(pole, *ants);

    std::cout << "Svet has been sucesfully created with " << numberOfAnts << " ants, width " << svetToReturn->getWidth()
              << " and height " << svetToReturn->getHeight() << std::endl;

    int choice = MenuControl::readInput(1, 2, "Do you want to randomly generate colors?\n1. Yes\n2. No\n");

    if (choice == 1)
    {
        svetToReturn->generateRandomColors();
    }
    return svetToReturn;
}

void MenuControl::printSvet(Svet* svet)
{
    if (svet == nullptr)
    {
        std::cout << "Svet is not generated yet! Generate one and try again!" << std::endl;
        return;
    }

    svet->printSvet();
}
