//
// Created by ghost on 22. 12. 2022.
//

#ifndef MRAVEC_MRAVECPRIAMY_H
#define MRAVEC_MRAVECPRIAMY_H

#include "../Mravec.h"

namespace mravec {

    class MravecPriamy: public Mravec {
    public:

        explicit MravecPriamy(int xPos=0, int yPos=0, Smer direction=Smer::NORTH);

        void mravecLogic(Policko &policko, int maxX, int maxY) override;

        Mravec* makeCopy() override;

        ~MravecPriamy() = default;
    };

} // mravec

#endif //MRAVEC_MRAVECPRIAMY_H
