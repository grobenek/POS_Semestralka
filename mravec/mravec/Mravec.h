#ifndef MRAVEC_MRAVEC_H
#define MRAVEC_MRAVEC_H

#include "../plocha/pole/Pole.h"
#include "smer/Smer.h"

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

        void shiftInDirection();

        Smer turnMravec(bool isLeftTurn);

        ~Mravec() = default;

    protected:
        virtual void mravecLogic(Policko& policko) = 0;
    };

} // mravec

#endif //MRAVEC_MRAVEC_H