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

    Policko() : color(BLACK), ants(){};

    virtual ~Policko();

    TypPolicka getColor() const;

    void setColor(TypPolicka pColor);

    void changeColor();

    void addAnt(mravec::Mravec* ant);

    std::string getStringRepresentation() const;
};

#endif //MRAVEC_POLICKO_H
