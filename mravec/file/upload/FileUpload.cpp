//
// Created by Peter Szathmáry on 27/12/2022.
//

#include <iostream>
#include <sys/stat.h>
#include "FileUpload.h"
#include "../../mravec/inverzny/MravecInverzny.h"

FileUpload::FileUpload(const std::string& fileName)
{
    struct stat st = {0};

    if (stat(this->directoryName, &st) == -1) {
        mkdir(this->directoryName, 0700);
    }

    this->file = std::ofstream(this->directoryName+fileName);
}

void FileUpload::saveSvetIntoFile(Svet& svet)
{
    auto* antsInSvet = svet.getCurrentAnts();
    int numberOfAnts = antsInSvet->size();
    int width = svet.getWidth();
    int height = svet.getHeight();
    std::string colors = svet.getStringRepresentationOfColors();

    this->file << numberOfAnts << std::endl;

    // type of ant
    for (int i = 0; i < numberOfAnts; ++i)
    {
        auto* ant = antsInSvet->at(i);
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
        this->file << antsInSvet->at(i)->getRowPos() << " " << antsInSvet->at(i)->getColumnPos() << std::endl;
    }

    this->file << width << " " << height << std::endl;
    this->file << colors << std::endl;

    for (auto* ant: *antsInSvet)
    {
        delete ant;
    }
    antsInSvet->clear();
    delete antsInSvet;
}

FileUpload::~FileUpload()
{
    this->file.close();
}
