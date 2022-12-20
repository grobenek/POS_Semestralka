//
// Created by Peter Szathmáry on 20/12/2022.
//

#include "Policko.h"

Policko::Policko(TypPolicka typPolicka) : typPolicka(typPolicka)
{}

TypPolicka Policko::getTypPolicka() const
{
    return typPolicka;
}

void Policko::setTypPolicka(TypPolicka pTypPolicka)
{
    Policko::typPolicka = pTypPolicka;
}

void Policko::zmenTypPolicka()
{
    this->typPolicka == BIELE ? this->typPolicka = CIERNE : this->typPolicka = BIELE;
}

std::string Policko::getZnak() const
{
    if (this->typPolicka == BIELE)
    {
        return "\033[47m \033[0m";
    } else
    {
        return "\033[40m \033[0m";
    }
}
