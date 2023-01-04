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
    std::cout << "Press 'enter' to start the application." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Start" << std::endl;
        std::cout << "2. Change position of ants" << std::endl;
        std::cout << "3. Change position of black" << std::endl;
        std::cout << "4. Change width and height of field" << std::endl;
        std::cout << "5. Change number of ants" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Select choice: ";

        char choice;
        std::cin.clear();
        std::cin >> choice;

        if (choice == '1') {
            std::cout << "Pre pauzu simulacie stlacte p." << std::endl;
            sleep(3);
            svet->generateRandomColors();
            svet->printSvet();

            Simulacia simulation(10, svet);
            simulation.simulation();
        } else if (choice == '2') {
            // Change position of ants
        } else if (choice == '3') {
            // Change position of black
        } else if (choice == '4') {
            // Change width and height of field
        } else if (choice == '5') {
            // Change number of ants
        } else if (choice == '0') {
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    delete svet;

    system("leaks mravec");
    return 0;
}
