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
    //TODO generacia vo svete nie v poli
    this->pole->generateRandomColors();
}
