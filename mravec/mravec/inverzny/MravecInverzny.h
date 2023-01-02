#include "../Mravec.h"
#ifndef MRAVEC_MRAVECINVERZNY_H
#define MRAVEC_MRAVECINVERZNY_H

namespace mravec {

    class MravecInverzny: public Mravec {
    public:

        MravecInverzny(int xPos, int yPos, Smer direction);

        void mravecLogic(Policko& policko, int maxX, int maxY) override;

        Mravec* makeCopy() override;

        ~MravecInverzny() = default;
    };

} // mravec

#endif //MRAVEC_MRAVECINVERZNY_H
