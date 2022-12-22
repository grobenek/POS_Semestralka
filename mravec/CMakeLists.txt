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
        mravec/priamy/MravecPriamy.cpp mravec/priamy/MravecPriamy.h)
