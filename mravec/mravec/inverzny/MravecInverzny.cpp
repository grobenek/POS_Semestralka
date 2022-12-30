#include "MravecInverzny.h"

namespace mravec {
    void MravecInverzny::mravecLogic(Policko& policko, int maxX, int maxY) {
        if (policko.getColor() == TypPolicka::WHITE) {
            this->turnMravec(true);
        } else {
            this->turnMravec(false);
        }

        policko.changeColor();
        this->shiftInDirection(maxX, maxY);
    }

    MravecInverzny::MravecInverzny(int xPos, int yPos, Smer direction) : Mravec(xPos, yPos, direction)
    {}
} // mravec