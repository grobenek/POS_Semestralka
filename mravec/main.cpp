#include <iostream>
#include <unistd.h>
#include "plocha/pole/Pole.h"
#include "svet/Svet.h"
#include "file/upload/FileUpload.h"
#include "simulacia/Simulacia.h"
#include "file/download/FileDownload.h"
#include "mravec/priamy/MravecPriamy.h"
#include "mravec/inverzny/MravecInverzny.h"

int main()
{
    Pole* pole = new Pole(10, 10);

    auto* ants = new std::vector<mravec::Mravec *>;

    auto* antPriamy = new mravec::MravecPriamy();
    auto* antPriamy2 = new mravec::MravecPriamy();
    auto* antPriamy3 = new mravec::MravecPriamy();
    auto* antPriamy4 = new mravec::MravecPriamy();
    auto* antInverzny = new mravec::MravecInverzny();
    auto* antInverzny2 = new mravec::MravecInverzny();
    auto* antInverzny3 = new mravec::MravecInverzny();
    auto* antInverzny4 = new mravec::MravecInverzny();

    ants->push_back(antPriamy);
    ants->push_back(antPriamy2);
    ants->push_back(antPriamy3);
    ants->push_back(antPriamy4);
    ants->push_back(antInverzny);
    ants->push_back(antInverzny2);
    ants->push_back(antInverzny3);
    ants->push_back(antInverzny4);

    Svet* svet = new Svet(pole, *ants);
    printf("Pre pauzu simulacie stlacte p.\n");
    sleep(5);
    svet->generateRandomColors();
    svet->printSvet();

    Simulacia simulation(10, svet);
    simulation.simulation();
    delete svet;

    system("leaks mravec");
    return 0;
}
