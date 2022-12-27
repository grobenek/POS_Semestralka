//
// Created by Peter Szathmáry on 27/12/2022.
//

#include "FileUpload.h"

FileUpload::FileUpload(const char* fileName)
{
    this->file = std::ofstream(fileName);
}

void FileUpload::saveSvetIntoFile(Svet& svet)
{
    // pocet mravcov
    // x a y kazdeho mravca
    // vyska a sirka pola
    // WBWBWBBBWBWB podla farby kazdeho pola

    //TODO dorobit
}

FileUpload::~FileUpload()
{
    this->file.close();
}
