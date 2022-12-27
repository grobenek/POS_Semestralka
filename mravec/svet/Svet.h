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
    std::vector<mravec::Mravec*> ants;

public:
    Svet(Pole* pole, const std::vector<mravec::Mravec*>& ants) : pole(pole), ants(ants)
    {}

    ~Svet()
    {
        delete this->pole;
        this->ants.clear();
    }

    void printSvet();

    void changeColorOfPolicko(int x, int y);

    void generateRandomColorsOfPole();

    void generatePositionsForAnts();

    void generateRandomColors();

    void changePositionOfAnt(mravec::Mravec& ant, int x, int y);

};


#endif //MRAVEC_SVET_H
