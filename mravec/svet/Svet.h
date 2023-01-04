//
// Created by Peter Szathmáry on 27/12/2022.
//

#ifndef MRAVEC_SVET_H
#define MRAVEC_SVET_H

#include <tuple>
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
            auto randomPositions = pole->generatePositionForAnt();

            ant->setXPos(std::get<0>(randomPositions));
            ant->setYPos(std::get<1>(randomPositions));
            ant->setDirection(static_cast<Smer>(std::get<2>(randomPositions)));

            auto* copy = ant->makeCopy();
            this->pole->getPolicko(ant->getRowPos(), ant->getColumnPos())->addAnt(copy);
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

    std::string getColorOfPolicko(int x, int y);

    void generateRandomColorsOfPole();

    std::tuple<int, int, int> generatePositionsForAnt();

    void generateRandomColors();

    int getNumberOfAnts() const;

    int getWidth();

    std::vector<mravec::Mravec*>* getCurrentAnts();

    void shiftAllAnts();

    void killAllExcessiveAnts();

    void changePositionOfAnt(mravec::Mravec* ant, Policko* currentPolicko, Policko* newPolicko);

    int getHeight();

    std::string getStringRepresentationOfColors();

    void tick();

    void addAnt(mravec::Mravec* ant);

    void deleteAllAnts();

    Policko* getPolicko(int x, int y);
};


#endif //MRAVEC_SVET_H
