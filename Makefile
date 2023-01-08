all:
    g++ -c command/MenuControl.cpp
    g++ -c connections/client/Client.cpp
    g++ -c connections/server/Server.cpp
    g++ -c file/download/FileDownload.cpp
    g++ -c file/upload/FileUpload.cpp
    g++ -c mravec/Mravec.cpp
    g++ -c mravec/inverzny/MravecInverzny.cpp
    g++ -c mravec/priamy/MravecPriamy.cpp
    g++ -c plocha/pole/Pole.cpp
    g++ -c plocha/policko/Policko.cpp
    g++ -c simulacia/Simulacia.cpp
    g++ -c svet/Svet.cpp
    g++ -c main.cpp
    g++ main.o Client.o Server.o FileDownload.o FileUpload.o Mravec.o 
MravecInverzny.o MravecPriamy.o Pole.o Policko.o Simulacia.o Svet.o 
MenuControl.o -o mravecFinal -pthread
server: all
    ./mravecFinal server
client: all
    ./mravecFinal client
clean:
    rm -f *.o
