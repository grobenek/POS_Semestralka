#include "Mravec.h"

namespace mravec {
    Mravec::Mravec(int xPos, int yPos, Smer direction) {
        this->row = xPos;
        this->column = yPos;
        this->direction = direction;
        this->movedThisRound = false;
    }

    int Mravec::getRowPos() const {
        return row;
    }

    void Mravec::setXPos(int xPos) {
        Mravec::row = xPos;
    }

    int Mravec::getColumnPos() const {
        return column;
    }

    void Mravec::setYPos(int yPos) {
        Mravec::column = yPos;
    }

    Smer Mravec::getDirection() const {
        return direction;
    }

    void Mravec::setDirection(Smer direction) {
        Mravec::direction = direction;
    }

    bool Mravec::isMovedThisRound() const {
        return movedThisRound;
    }

    void Mravec::setMovedThisRound(bool movedThisRound) {
        Mravec::movedThisRound = movedThisRound;
    }

    void Mravec::shiftInDirection(int maxX, int maxY) {
        // TODO rekurzia, ked bude cas vymysliet inak (mala by sa opakovat len raz ked tak)
        if (this->direction == EAST || this->direction == WEST) {
            if (this->checkXPosition(maxX)) {
                this->turnOppositeDirection();
                this->shiftInDirection(maxX, maxY);
                return;
            }
        } else {
            if (this->checkYPosition(maxY)) {
                this->turnOppositeDirection();
                this->shiftInDirection(maxX, maxY);
                return;
            }
        }

        switch(this->getDirection()) {
            case NORTH:
                this->row--;
                break;
            case SOUTH:
                this->row++;
                break;
            case EAST:
                this->column++;
                break;
            case WEST:
                this->column--;
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
        return this->row - 1 < 0 || this->row + 1 > maxX;
    }

    bool Mravec::checkYPosition(int maxY) {
        // TODO ked tak to zmenit
        return this->column - 1 < 0 || this->column + 1 > maxY;
    }

    void Mravec::turnOppositeDirection() {
        this->direction = static_cast<Smer>((this->direction + 2) % 4);
    }
} // mravec