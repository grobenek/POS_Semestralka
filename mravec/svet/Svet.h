//
// Created by Peter Szathmáry on 27/12/2022.
//

#ifndef MRAVEC_SVET_H
#define MRAVEC_SVET_H

#include "../plocha/pole/Pole.h"
#include "../mravec/Mravec.h"

class Svet
{
private:
    Pole* pole;

public:
    Svet(Pole* pole, const std::vector<mravec::Mravec*>& ants) : pole(pole)
    {
        for (auto ant : ants)
        {
            auto* copy = ant->makeCopy();
            this->pole->getPolicko(ant->getXPos(), ant->getYPos())->addAnt(copy);
        }

        for (auto ant : ants)
        {
            delete ant;
        }
    }

    ~Svet()
    {
        delete this->pole;
    }

    void printSvet();

    void changeColorOfPolicko(int x, int y);

    void generateRandomColorsOfPole();

    void generatePositionsForAnts();

    void generateRandomColors();

    int getNumberOfAnts() const;

    int getWidth();

    std::vector<mravec::Mravec*>* getCurrentAnts();

    void changePositionOfAnt(mravec::Mravec& ant, int x, int y);

    int getHeight();

    std::string getStringRepresentationOfColors();
};


#endif //MRAVEC_SVET_H
