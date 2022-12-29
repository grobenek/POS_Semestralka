//
// Created by Peter Szathmáry on 27/12/2022.
//

#include "Svet.h"

void Svet::printSvet()
{
    this->pole->printBoard();
}

void Svet::changeColorOfPolicko(int x, int y)
{
    this->pole->changeColorOfPolicko(x, y);
}

void Svet::generateRandomColorsOfPole()
{
    this->pole->generateRandomColors();
}

void Svet::generatePositionsForAnts()
{

}

void Svet::generateRandomColors()
{
    this->pole->generateRandomColors();
}

int Svet::getNumberOfAnts() const
{
    return this->ants.size();
}

int Svet::getWidth()
{
    return this->pole->getWidth();
}

int Svet::getHeight()
{
    return this->pole->getHeight();
}

std::string Svet::getStringRepresentationOfColors()
{
    return this->pole->getStringRepresentationOfColors();
}

mravec::Mravec* Svet::getAnt(int index)
{
    return this->ants.at(index);
}
