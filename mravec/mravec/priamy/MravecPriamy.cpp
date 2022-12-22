//
// Created by ghost on 22. 12. 2022.
//

#include "MravecPriamy.h"

namespace mravec {
    void MravecPriamy::mravecLogic(Policko &policko) {
        if (policko.getColor() == TypPolicka::WHITE) {
            this->turnMravec(false);
        } else {
            this->turnMravec(true);
        }

        policko.changeColor();
        this->shiftInDirection();
    }
} // mravec