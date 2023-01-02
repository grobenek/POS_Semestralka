//
// Created by ghost on 22. 12. 2022.
//

#include "MravecPriamy.h"

namespace mravec {
    void MravecPriamy::mravecLogic(Policko &policko, int maxX, int maxY) {
        if (this->isMovedThisRound()) {
            return;
        }

        if (policko.getColor() == TypPolicka::WHITE) {
            this->turnMravec(false);
        } else {
            this->turnMravec(true);
        }

        policko.changeColor();
        this->shiftInDirection(maxX, maxY);
        this->setMovedThisRound(true);
    }

    MravecPriamy::MravecPriamy(int xPos, int yPos, Smer direction) : Mravec(xPos, yPos, direction)
    {}

    Mravec* MravecPriamy::makeCopy()
    {
        return new MravecPriamy(this->getRowPos(), this->getColumnPos(), this->getDirection());
    }
} // mravec