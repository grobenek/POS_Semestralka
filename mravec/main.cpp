#include <iostream>
#include "plocha/pole/Pole.h"
#include "svet/Svet.h"
#include "file/upload/FileUpload.h"
#include "simulacia/Simulacia.h"

int main()
{
//    Pole* pole = new Pole(10, 10);
//
//    auto* ants = new std::vector<mravec::Mravec *>;
//
//    Svet* svet = new Svet(pole, *ants);

//    svet->generateRandomColors();
//    svet->printSvet();
//
//    FileUpload fileUpload("skuska.txt");
//    fileUpload.saveSvetIntoFile(*svet);

    Simulacia simulacia(100);
    simulacia.simulation();


//    delete svet;

    system("leaks mravec");
    return 0;
}
