//
// Created by Peter Szathmáry on 20/12/2022.
//

#include <iostream>
#include <chrono>
#include <sstream>
#include <tuple>
#include "Pole.h"

Pole::Pole(int pWidth, int pHeight) : width(pWidth), height(pHeight)
{
    if (pWidth <= 0 || pHeight <= 0)
    {
        throw std::invalid_argument("Width or Height is 0!");
    }

    // pointer to pointer
    this->board = new Policko* [this->width];

    for (int width = 0; width < pWidth; ++width)
    {
        this->board[width] = new Policko[pHeight];
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

/**
 * Changes color of Policko on given x and y
 * @param x x of Policko
 * @param y y of Policko
 */
void Pole::changeColorOfPolicko(int x, int y)
{
    if (x < 0 || y < 0)
    {
        throw std::invalid_argument("Width or Height is negative number!");
    }
    if (x > this->width || y > this->height)
    {
        throw std::invalid_argument("x or y is greater than width or height");
    }

    this->board[x][y].changeColor();
}

Policko* Pole::getPolicko(int x, int y) const {
    return &this->board[x][y];
}

std::string Pole::getStringRepresentationOfColors() const
{
    std::stringstream stringstream;

    for (int i = 0; i < this->width; ++i)
    {
        for (int j = 0; j < this->height; ++j)
        {
            if (this->board[i][j].getColor() == WHITE)
            {
                stringstream << "W";
            } else
            {
                stringstream << "B";
            }
        }
    }
    return stringstream.str();
}

std::tuple<int, int , int> Pole::generatePositionForAnt()
{
    auto uniformDistributionWidth = std::uniform_int_distribution<int>(0, this->width - 1);
    auto uniformDistributionHeight = std::uniform_int_distribution<int>(0, this->height - 1);

    int randomHeight = uniformDistributionHeight(this->randomNumberGenerator);
    int randomWidth = uniformDistributionWidth(this->randomNumberGenerator);
    int randomDirection = this->uniformIntDistribution(this->randomNumberGenerator) % 4;

    return std::make_tuple(randomWidth, randomHeight, randomDirection);
}
