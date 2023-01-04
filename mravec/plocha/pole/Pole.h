//
// Created by Peter Szathmáry on 20/12/2022.
//

#ifndef MRAVEC_POLE_H
#define MRAVEC_POLE_H


#include <random>
#include "../policko/Policko.h"

class Pole
{
private:
    int width;
    int height;
    Policko** board;
    std::mt19937 randomNumberGenerator;
    std::uniform_int_distribution<int> uniformIntDistribution;

public:
    Pole(int pWidth, int pHeight);

    void printBoard();

    void changeColorOfPolicko(int x, int y);

    void generateRandomColors();

    std::pair<int, int> generatePositionForAnt();

    std::string getStringRepresentationOfColors() const;

    int getWidth() const;

    int getHeight() const;

    Policko* getPolicko(int x, int y) const;

    ~Pole();
};


#endif //MRAVEC_POLE_H
