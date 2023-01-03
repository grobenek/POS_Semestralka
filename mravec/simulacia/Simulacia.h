//
// Created by ghost on 31. 12. 2022.
//

#ifndef MRAVEC_SIMULACIA_H
#define MRAVEC_SIMULACIA_H

#include <mutex>
#include <condition_variable>
#include "../svet/Svet.h"

class Simulacia {
private:
    Svet* svet;
    bool isStopped;
    std::mutex mutex;
    std::condition_variable cond_variable_control;
    std::condition_variable cond_variable_run;
    int numberOfSteps;

public:
    explicit Simulacia(int numberOfSteps, Svet* svet);

    void simulationRun();
    void simulationControl();
    void simulation();
};


#endif //MRAVEC_SIMULACIA_H
