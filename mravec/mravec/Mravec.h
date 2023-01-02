#ifndef MRAVEC_MRAVEC_H
#define MRAVEC_MRAVEC_H

#include "smer/Smer.h"
#include "../plocha/policko/Policko.h"

namespace mravec {

    class Mravec {
    private:
        int row;
        int column;
        Smer direction;
        bool movedThisRound;

    public:
        Mravec(int xPos, int yPos, Smer direction);

        int getRowPos() const;

        void setXPos(int xPos);

        int getColumnPos() const;

        void setYPos(int yPos);

        bool isMovedThisRound() const;

        void setMovedThisRound(bool movedThisRound);

        Smer getDirection() const;

        void setDirection(Smer direction);

        void shiftInDirection(int maxX, int maxY);

        Smer turnMravec(bool isLeftTurn);

        virtual ~Mravec() = default;

        virtual void mravecLogic(Policko& policko, int maxX, int maxY) = 0;

        virtual Mravec* makeCopy() = 0;


    private:
        bool checkXPosition(int maxX);

        bool checkYPosition(int maxY);

        void turnOppositeDirection();
    };

} // mravec

#endif //MRAVEC_MRAVEC_H
