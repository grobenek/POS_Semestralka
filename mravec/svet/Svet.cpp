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
    int numberOfAnts = 0;
    for (int i = 0; i < this->pole->getWidth(); ++i)
    {
        for (int j = 0; j < this->pole->getHeight(); ++j)
        {
            numberOfAnts += this->pole->getPolicko(i, j)->getNumberOfAnts();
        }
    }
    return numberOfAnts;
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

std::vector<mravec::Mravec*>* Svet::getCurrentAnts()
{
    auto* antsToReturn = new std::vector<mravec::Mravec*>();

    for (int i = 0; i < this->pole->getWidth(); ++i)
    {
        for (int j = 0; j < this->pole->getHeight(); ++j)
        {
            int numberOfAnts = this->pole->getPolicko(i, j)->getNumberOfAnts();
            if (numberOfAnts > 0)
            {
                for (int k = 0; k < numberOfAnts; ++k)
                {
                    antsToReturn->push_back(this->pole->getPolicko(i, j)->getAnt(k)->makeCopy());
                }
            }
        }
    }
    return antsToReturn;
}

void Svet::shiftAllAnts() {
    for (int i = 0; i < this->pole->getWidth(); ++i)
    {
        for (int j = 0; j < this->pole->getHeight(); ++j)
        {
            if (this->pole->getPolicko(i, j)->getNumberOfAnts() > 0) {
                Policko* currentPolicko = this->pole->getPolicko(i, j);
                std::vector<mravec::Mravec*> currentAnts = currentPolicko->getAnts();

                for (mravec::Mravec* currentAnt : currentAnts) {
                    if (!currentAnt->isMovedThisRound()) {
                        currentAnt->mravecLogic(*currentPolicko, this->pole->getWidth(), this->pole->getHeight());

                        Policko* shiftedPolicko = this->pole->getPolicko(currentAnt->getRowPos(), currentAnt->getColumnPos());
                        this->changePositionOfAnt(currentAnt, currentPolicko, shiftedPolicko);
                    }
                }
            }
        }
    }
}

void Svet::changePositionOfAnt(mravec::Mravec *ant, Policko* currentPolicko, Policko* newPolicko) {
    if (currentPolicko == nullptr || newPolicko == nullptr) {
        return;
    }

    if (ant != nullptr) {
        newPolicko->addAnt(ant);
        currentPolicko->removeAnt(0);
    }
}

void Svet::killAllExcessiveAnts() {
    for (int i = 0; i < this->pole->getWidth(); ++i)
    {
        for (int j = 0; j < this->pole->getHeight(); ++j)
        {
            Policko* policko = this->pole->getPolicko(i, j);
            policko->killExcessiveAnts();

            if (policko->getNumberOfAnts() > 0) {
                policko->getAnt(0)->setMovedThisRound(false);
            }
        }
    }
}
