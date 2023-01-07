//
// Created by Peter Szathmáry on 04/01/2023.
//

#ifndef MRAVEC_MENUCONTROL_H
#define MRAVEC_MENUCONTROL_H


#include "../svet/Svet.h"

class MenuControl
{
public:
    static std::string getMainMenuString();
    static std::string getConfigureSimulationString();
    static std::string displaySaveSimulation();
    static std::string displayLoadSimulation();
    static void addAnt(Svet* svet);
    static void generateColorsForSvet(Svet* svet);
    static void deleteAllAnts(Svet* svet);
    static void changeColorOfPolicko(Svet* svet);
    static void saveSvetLocaly(Svet* svet);

    static int readInput(int minRange, int maxRange, const std::string& stringToPrint);

    static void changePositionOfAnt(Svet* svet);

    static Svet* deleteSvet(Svet* svet);

    static Svet* loadSvetLocaly(Svet* svet, const std::string& loadDirectoryName);

    static Svet* runSimulation(Svet* svet);

    static Svet* createSvet(Svet* svet);

    static int getNumberOfSteps();

    static void printSvet(Svet* svet);
};


#endif //MRAVEC_MENUCONTROL_H
