#include "MravecInverzny.h"

namespace mravec {
    void MravecInverzny::mravecLogic(Policko& policko, int maxX, int maxY) {
        if (this->isMovedThisRound()) {
            return;
        }

        if (policko.getColor() == TypPolicka::WHITE) {
            this->turnMravec(true);
        } else {
            this->turnMravec(false);
        }

        policko.changeColor();
        this->shiftInDirection(maxX, maxY);
        this->setMovedThisRound(true);
    }

    MravecInverzny::MravecInverzny(int xPos, int yPos, Smer direction) : Mravec(xPos, yPos, direction)
    {}

    Mravec* MravecInverzny::makeCopy()
    {
        return new MravecInverzny(this->getRowPos(), this->getColumnPos(), this->getDirection());
    }
} // mravec