#include <iostream>
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

    auto* antPriamy = new mravec::MravecPriamy(1, 2, NORTH);
    auto* antInverzny = new mravec::MravecInverzny(2, 1, NORTH);

    ants->push_back(antPriamy);
    ants->push_back(antInverzny);

    Svet* svet = new Svet(pole, *ants);

    svet->generateRandomColors();
    svet->printSvet();

    FileUpload fileUpload("skuska.txt");
    fileUpload.saveSvetIntoFile(*svet);

    std::cout << std::endl << std::endl;

    FileDownload fileDownload;
    auto* downloadedSvet = fileDownload.createSvetFromFile("skuska.txt");

    downloadedSvet->printSvet();

    delete svet;

    system("leaks mravec");
    return 0;
}
