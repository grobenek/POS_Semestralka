//
// Created by Peter Szathmáry on 27/12/2022.
//

#ifndef MRAVEC_FILEUPLOAD_H
#define MRAVEC_FILEUPLOAD_H


#include <cstdio>
#include <fstream>
#include "../../svet/Svet.h"

class FileUpload
{
private:
    std::ofstream file;

public:
    explicit FileUpload(const char* fileName);

    virtual ~FileUpload();

    void saveSvetIntoFile(Svet& svet);
};


#endif //MRAVEC_FILEUPLOAD_H
