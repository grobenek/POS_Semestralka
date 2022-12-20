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
    TypPolicka typPolicka;

public:
    explicit Policko(TypPolicka typPolicka);

    TypPolicka getTypPolicka() const;

    void setTypPolicka(TypPolicka pTypPolicka);

    void zmenTypPolicka();

    std::string getZnak() const;
};

#endif //MRAVEC_POLICKO_H
