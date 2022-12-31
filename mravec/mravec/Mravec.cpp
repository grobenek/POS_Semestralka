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

    void Mravec::shiftInDirection(int maxX, int maxY) {
        // TODO rekurzia, ked bude cas vymysliet inak (mala by sa opakovat len raz ked tak)
        if (this->checkXPosition(maxX)) {
            this->turnOppositeDirection();
            this->shiftInDirection(maxX, maxY);
            return;
        }

        if (this->checkYPosition(maxY)) {
            this->turnOppositeDirection();
            this->shiftInDirection(maxX, maxY);
            return;
        }

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

    bool Mravec::checkXPosition(int maxX) {
        // TODO ked tak to zmenit
        return (this->xPos + 1 <= maxX && this->xPos + 1 >= 0) || (this->xPos - 1 <= maxX && this->xPos - 1 >= 0);
    }

    bool Mravec::checkYPosition(int maxY) {
        // TODO ked tak to zmenit
        return (this->yPos + 1 <= maxY && this->yPos + 1 >= 0) || (this->yPos - 1 <= maxY && this->yPos - 1 >= 0);
    }

    void Mravec::turnOppositeDirection() {
        this->direction = static_cast<Smer>((this->direction + 2) % 4);
    }
} // mravec