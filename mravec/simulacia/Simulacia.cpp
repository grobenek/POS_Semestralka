//
// Created by ghost on 31. 12. 2022.
//

#include <thread>
#include <iostream>
#include "Simulacia.h"

void Simulacia::simulationRun() {
    // used because of wait function
    // while waiting - mutex is unlocked
    // after wait - mutex is locked
    std::unique_lock<std::mutex> lock(mutex);

    for (int i = 0; i < this->numberOfSteps; ++i) {
        if (this->isStopped) {
            // [this] - object is used in lambda function
            std::cout << "Locked" << std::endl;
            this->cond_variable_control.wait(lock, [this]{ return !isStopped; });
        }
        this->mutex.unlock();

        std::cout << "Running" << std::endl;
        // posun mravce
        // vypis plochu
        // wait 1sec
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Simulacia::simulationControl() {
    while (true) {
        std::string a;
        std::cout << "Zadaj prikaz: ";
        std::cin >> a;

        if (a == "s") {
            this->mutex.lock();
            this->isStopped = true;
            this->mutex.unlock();
        } if (a == "start") {
            this->mutex.lock();
            this->isStopped = false;
            this->cond_variable_control.notify_one();
            this->mutex.unlock();
        }
    }
}

void Simulacia::simulation() {
    std::thread simulationRunThread(&Simulacia::simulationRun, this);
    std::thread simulationControlThread(&Simulacia::simulationControl, this);

    simulationRunThread.join();
    simulationControlThread.join();
}

Simulacia::Simulacia(int numberOfSteps) : numberOfSteps(numberOfSteps), isStopped(false) {}
