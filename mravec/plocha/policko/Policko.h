//
// Created by Peter Szathmáry on 20/12/2022.
//

#ifndef MRAVEC_POLICKO_H
#define MRAVEC_POLICKO_H

#include <string>
#include "../typPolicka/TypPolicka.h"

class Policko
{
private:
    TypPolicka color;

public:
    explicit Policko(TypPolicka pColor);

    Policko() : color(BLACK){};

    TypPolicka getColor() const;

    void setColor(TypPolicka pColor);

    void changeColor();

    std::string getStringRepresentation() const;
};

#endif //MRAVEC_POLICKO_H
