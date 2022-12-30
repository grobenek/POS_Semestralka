//
// Created by Peter Szathmáry on 27/12/2022.
//

#include "FileUpload.h"
#include "../../mravec/inverzny/MravecInverzny.h"

FileUpload::FileUpload(const char* fileName)
{
    this->file = std::ofstream(fileName);
}

void FileUpload::saveSvetIntoFile(Svet& svet)
{
    int numberOfAnts = svet.getNumberOfAnts();
    int width = svet.getWidth();
    int height = svet.getHeight();
    std::string colors = svet.getStringRepresentationOfColors();

    this->file << numberOfAnts << std::endl;

    // type of ant
    for (int i = 0; i < numberOfAnts; ++i)
    {
        auto* ant = svet.getAnt(i);
        std::string stringDirection;

        switch (ant->getDirection())
        {
            case NORTH:
                stringDirection = "N";
                break;
            case EAST:
                stringDirection = "E";
                break;
            case WEST:
                stringDirection = "W";
                break;
            case SOUTH:
                stringDirection = "S";
                break;
            default:
                throw std::runtime_error("Unexpected direction of ant found!");
        }

        if (dynamic_cast<mravec::MravecInverzny*>(ant) != nullptr)
        {
            this->file << "I " << stringDirection << std::endl;
        } else
        {
            this->file << "P " << stringDirection << std::endl;
        }
    }

    for (int i = 0; i < numberOfAnts; ++i)
    {
        this->file << svet.getAnt(i)->getXPos() << " " << svet.getAnt(i)->getYPos() << std::endl;
    }

    this->file << width << " " << height << std::endl;
    this->file << colors;
}

FileUpload::~FileUpload()
{
    this->file.close();
}
