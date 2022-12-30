//
// Created by Peter Szathmáry on 27/12/2022.
//

#ifndef MRAVEC_FILEDOWNLOAD_H
#define MRAVEC_FILEDOWNLOAD_H


#include <fstream>
#include "../../svet/Svet.h"

class FileDownload
{
private:
    std::ifstream file;

public:
    FileDownload();

    virtual ~FileDownload();

    Svet* createSvetFromFile(const std::string& fileName);
};


#endif //MRAVEC_FILEDOWNLOAD_H
