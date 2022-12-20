//
// Created by Peter Szathmáry on 20/12/2022.
//

#include <iostream>
#include "Pole.h"

Pole::Pole(int pWidth, int pHeight) : width(pWidth), height(pHeight)
{
    if (pWidth && pHeight <= 0)
    {
        throw std::invalid_argument("Width or Height is 0!");
    }

    this->width = pWidth;
    this->height = pHeight;

    // pointer to pointer
    this->board = new Policko* [this->width];

    for (int i = 0; i < pWidth; ++i)
    {
        this->board[pWidth] = new Policko[pHeight];
    }

    // random generator
    this->uniformIntDistribution = std::uniform_int_distribution<int>(0, 100);
    this->randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

Pole::~Pole()
{
    for (int i = 0; i < this->width; ++i)
    {
        delete[] this->board[i];
    }

    delete[] this->board;
}

int Pole::getWidth() const
{
    return width;
}

int Pole::getHeight() const
{
    return height;
}

void Pole::printBoard()
{
    for (int width = 0; width < this->width; ++width)
    {
        for (int height = 0; height < this->height; ++height)
        {
            std::cout << this->board[width][height].getStringRepresentation();
        }
        std::cout << std::endl;
    }
}

void Pole::generateRandomColors()
{
    for (int width = 0; width < this->width; ++width)
    {
        for (int height = 0; height < this->height; ++height)
        {
            TypPolicka color;
            // number from 0 to 100
            int randomNumber = this->uniformIntDistribution(this->randomNumberGenerator);
            randomNumber <= 50 ? color = WHITE : color = BLACK;

            this->board[width][height].setColor(color);
        }
    }
}
