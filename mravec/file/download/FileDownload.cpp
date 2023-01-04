//
// Created by Peter Szathmáry on 27/12/2022.
//

#include <iostream>
#include <sstream>
#include "FileDownload.h"
#include "../../mravec/priamy/MravecPriamy.h"
#include "../../mravec/inverzny/MravecInverzny.h"

FileDownload::~FileDownload()
{
    if (this->file.is_open())
    {
        this->file.close();
    }
}

Svet* FileDownload::createSvetFromFile(const std::string& fileName)
{
    int numberOfAnts;
    int width;
    int height;
    std::string colors;

    this->file = std::ifstream(fileName);

    if (!this->file.good())
    {
        throw std::runtime_error("File " + fileName + " could not be opened!");
    }

    std::string line;

    // number of ants
    std::getline(this->file, line);
    std::istringstream ss(line);
    ss >> numberOfAnts;

    // reading types of ants
    std::vector<mravec::Mravec*> ants;
    // true = Priamy, false = Inverzny
    bool typesOfAnts[numberOfAnts];
    std::string directionOfAnts[numberOfAnts];

    for (int i = 0; i < numberOfAnts; ++i)
    {
        std::getline(this->file, line);

        ss.clear();
        ss.str(line);

        std::string direction;
        std::string type;
        ss >> type;
        ss >> direction;

        if (type == "P")
        {
            typesOfAnts[i] = false;
        } else
        {
            typesOfAnts[i] = true;
        }

        directionOfAnts[i] = direction;
    }
    // creating ants
    for (int i = 0; i < numberOfAnts; ++i)
    {
        std::getline(this->file, line);

        int x = -1;
        int y = -1;

        ss.clear();
        ss.str(line);

        ss >> x;
        ss >> y;

        Smer direction;

        if (directionOfAnts[i] == "N")
        {
            direction = NORTH;
        } else if (directionOfAnts[i] == "S")
        {
            direction = SOUTH;
        } else if (directionOfAnts[i] == "W")
        {
            direction = WEST;
        } else
        {
            direction = EAST;
        }

        if (typesOfAnts[i])
        {
            auto* mravec = new mravec::MravecPriamy(x, y, direction);
            ants.push_back(mravec);
        } else
        {
            auto* mravec = new mravec::MravecInverzny(x, y, direction);
            ants.push_back(mravec);
        }
    }

    // reading width and height
    std::getline(this->file, line);
    ss.clear();
    ss.str(line);
    ss >> width;
    ss >> height;

    Pole* pole = new Pole(width, height);

    // reading colors of Policko
    std::getline(this->file, line);

    int counter = 0;
    for (int i = 0; i < pole->getWidth(); ++i)
    {
        for (int j = 0; j < pole->getHeight(); ++j)
        {
            if (line.at(counter) == 'B')
            {
                pole->changeColorOfPolicko(i, j);
            }
            counter++;
        }
    }

    Svet* svet = new Svet(pole, ants);
    return svet;
}
