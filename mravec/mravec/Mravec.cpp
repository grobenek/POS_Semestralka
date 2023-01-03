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

    void Mravec::shiftInDirection(int maxRow, int maxColumn) {
        // TODO rekurzia, ked bude cas vymysliet inak (mala by sa opakovat len raz ked tak)
        if (this->checkRowPosition(maxRow)) {
            this->turnOppositeDirection();
            this->shiftInDirection(maxRow, maxColumn);
            return;
        } else if (this->checkColumnPosition(maxColumn)) {
            this->turnOppositeDirection();
            this->shiftInDirection(maxRow, maxColumn);
            return;
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

    bool Mravec::checkRowPosition(int maxRow) {
        if (this->direction == SOUTH) {
            return this->row + 1 >= maxRow;
        } else if (this->direction == NORTH) {
            return this->row - 1 < 0;
        }

        return false;
    }

    bool Mravec::checkColumnPosition(int maxColumn) {
        if (this->direction == EAST) {
            return this->column + 1 >= maxColumn;
        } else if (this->direction == WEST) {
            return this->column - 1 < 0;
        }

        return false;
    }

    void Mravec::turnOppositeDirection() {
        this->direction = static_cast<Smer>((this->direction + 2) % 4);
    }
} // mravec