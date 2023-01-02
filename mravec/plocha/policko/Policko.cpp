//
// Created by Peter Szathmáry on 20/12/2022.
//

#include <iostream>
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
    if (!this->ants.empty() && this->color == WHITE)
    {
        return "\033[30m\033[47m O \033[0m";
    } else if (!this->ants.empty() && this->color == BLACK)
    {
        return "\033[37m\033[40m O \033[0m";
    } else
    {
        if (this->color == WHITE)
        {
            return "\033[47m \033[0m\033[47m \033[0m\033[47m \033[0m";
        } else
        {
            return "\033[40m \033[0m\033[40m \033[0m\033[40m \033[0m";
        }
    }
}

void Policko::addAnt(mravec::Mravec* ant)
{
    if (ant != nullptr)
    {
        this->ants.push_back(ant);
    }
}

Policko::~Policko()
{
    for (auto* ant: this->ants)
    {
        delete ant;
    }

    this->ants.clear();
}
