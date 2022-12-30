#ifndef MRAVEC_MRAVEC_H
#define MRAVEC_MRAVEC_H

#include "smer/Smer.h"
#include "../plocha/policko/Policko.h"

namespace mravec {

    class Mravec {
    private:
        int xPos;
        int yPos;
        Smer direction;

    public:
        Mravec(int xPos, int yPos, Smer direction);

        int getXPos() const;

        void setXPos(int xPos);

        int getYPos() const;

        void setYPos(int yPos);

        Smer getDirection() const;

        void setDirection(Smer direction);

        void shiftInDirection(int maxX, int maxY);

        Smer turnMravec(bool isLeftTurn);

        ~Mravec() = default;

        virtual void mravecLogic(Policko& policko, int maxX, int maxY) = 0;

    private:
        bool checkXPosition(int maxX);

        bool checkYPosition(int maxY);

        void turnOppositeDirection();
    };

} // mravec

#endif //MRAVEC_MRAVEC_H
