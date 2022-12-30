//
// Created by ghost on 22. 12. 2022.
//

#ifndef MRAVEC_MRAVECPRIAMY_H
#define MRAVEC_MRAVECPRIAMY_H

#include "../Mravec.h"

namespace mravec {

    class MravecPriamy: public Mravec {
    public:

        MravecPriamy(int xPos, int yPos, Smer direction);

        void mravecLogic(Policko &policko) override;

        ~MravecPriamy() = default;
    };

} // mravec

#endif //MRAVEC_MRAVECPRIAMY_H
