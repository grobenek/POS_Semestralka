//
// Created by Peter Szathmáry on 20/12/2022.
//

#ifndef MRAVEC_POLICKO_H
#define MRAVEC_POLICKO_H

#include <string>
#include <vector>
#include "../typPolicka/TypPolicka.h"
namespace mravec {
    class Mravec;
}

class Policko
{
private:
    TypPolicka color;
    std::vector<mravec::Mravec*> ants;

public:
    explicit Policko(TypPolicka pColor);

    Policko() : color(WHITE), ants(){};

    virtual ~Policko();

    TypPolicka getColor() const;

    void setColor(TypPolicka pColor);

    const std::vector<mravec::Mravec *> &getAnts() const;

    void changeColor();

    void addAnt(mravec::Mravec* ant);

    void removeAnt(int index);

    std::string getStringRepresentation() const;

    int getNumberOfAnts();

    mravec::Mravec* getAnt(int index);

    void killExcessiveAnts();
};

#endif //MRAVEC_POLICKO_H
