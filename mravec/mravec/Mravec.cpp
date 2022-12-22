#include "Mravec.h"

namespace mravec {
    Mravec::Mravec(int xPos, int yPos, Smer direction) {
        this->xPos = xPos;
        this->yPos = yPos;
        this->direction = direction;
    }

    int Mravec::getXPos() const {
        return xPos;
    }

    void Mravec::setXPos(int xPos) {
        Mravec::xPos = xPos;
    }

    int Mravec::getYPos() const {
        return yPos;
    }

    void Mravec::setYPos(int yPos) {
        Mravec::yPos = yPos;
    }

    Smer Mravec::getDirection() const {
        return direction;
    }

    void Mravec::setDirection(Smer direction) {
        Mravec::direction = direction;
    }

    void Mravec::shiftInDirection() {
        switch(this->getDirection()) {
            case NORTH:
                this->setYPos(-1);
                break;
            case SOUTH:
                this->setYPos(1);
                break;
            case EAST:
                this->setXPos(1);
                break;
            case WEST:
                this->setXPos(-1);
                break;
        }
    }

    Smer Mravec::turnMravec(bool isLeftTurn) {
        if (isLeftTurn) {
            this->direction = static_cast<Smer>((this->direction + 3) % 4);
        } else {
            this->direction = static_cast<Smer>((this->direction + 1) % 4);
        }

        return this->direction;
    }
} // mravec