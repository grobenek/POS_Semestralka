cmake_minimum_required(VERSION 3.18)
project(mravec)

set(CMAKE_CXX_STANDARD 14)

add_executable(mravec main.cpp
            plocha/policko/Policko.h
            plocha/policko/Policko.cpp
            plocha/typPolicka/TypPolicka.h
            plocha/pole/Pole.h
            plocha/pole/Pole.cpp
            mravec/Mravec.cpp
            mravec/Mravec.h
            mravec/inverzny/MravecInverzny.cpp
            mravec/inverzny/MravecInverzny.h
            mravec/smer/Smer.h
            mravec/priamy/MravecPriamy.cpp
            mravec/priamy/MravecPriamy.h
            svet/Svet.h
            svet/Svet.cpp
            file/upload/FileUpload.h
            file/upload/FileUpload.cpp
            file/download/FileDownload.h
            file/download/FileDownload.cpp
            simulacia/Simulacia.cpp
            simulacia/Simulacia.h command/MenuControl.h command/MenuControl.cpp connections/server/Server.cpp connections/server/Server.h connections/client/Client.cpp connections/client/Client.h)

target_link_libraries(mravec pthread)
