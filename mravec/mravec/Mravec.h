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
        explicit Mravec(int xPos=0, int yPos=0, Smer direction=Smer::NORTH);

        int getRowPos() const;

        void setXPos(int xPos);

        int getColumnPos() const;

        void setYPos(int yPos);

        bool isMovedThisRound() const;

        void setMovedThisRound(bool movedThisRound);

        Smer getDirection() const;

        void setDirection(Smer direction);

        void shiftInDirection(int maxRow, int maxColumn);

        Smer turnMravec(bool isLeftTurn);

        virtual ~Mravec() = default;

        virtual void mravecLogic(Policko& policko, int maxX, int maxY) = 0;

        virtual Mravec* makeCopy() = 0;


    private:
        bool checkRowPosition(int maxRow);

        bool checkColumnPosition(int maxColumn);

        void turnOppositeDirection();
    };

} // mravec

#endif //MRAVEC_MRAVEC_H
