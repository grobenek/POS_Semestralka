//
// Created by Peter Szathmáry on 27/12/2022.
//

#include "FileUpload.h"

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
