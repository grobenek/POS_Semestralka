#include "../Mravec.h"
#ifndef MRAVEC_MRAVECINVERZNY_H
#define MRAVEC_MRAVECINVERZNY_H

namespace mravec {

    class MravecInverzny: public Mravec {
    public:
        void mravecLogic(Policko& policko) override;

        ~MravecInverzny() = default;
    };

} // mravec

#endif //MRAVEC_MRAVECINVERZNY_H
