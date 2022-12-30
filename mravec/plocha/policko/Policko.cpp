//
// Created by Peter Szathmáry on 20/12/2022.
//

#include "Policko.h"

Policko::Policko(TypPolicka pColor) : color(pColor), ants()
{}

TypPolicka Policko::getColor() const
{
    return color;
}

void Policko::setColor(TypPolicka pColor)
{
    this->color = pColor;
}

void Policko::changeColor()
{
    this->color == WHITE ? this->setColor(BLACK) : this->setColor(WHITE);
}

std::string Policko::getStringRepresentation() const
{
    if (this->color == WHITE)
    {
        return "\033[47m \033[0m";
    } else
    {
        return "\033[40m \033[0m";
    }
}
