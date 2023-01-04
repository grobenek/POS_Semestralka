#include "../Mravec.h"
#ifndef MRAVEC_MRAVECINVERZNY_H
#define MRAVEC_MRAVECINVERZNY_H

namespace mravec {

    class MravecInverzny: public Mravec {
    public:

        explicit MravecInverzny(int xPos=0, int yPos=0, Smer direction=Smer::NORTH);

        void mravecLogic(Policko& policko, int maxX, int maxY) override;

        Mravec* makeCopy() override;

        ~MravecInverzny() = default;
    };

} // mravec

#endif //MRAVEC_MRAVECINVERZNY_H
