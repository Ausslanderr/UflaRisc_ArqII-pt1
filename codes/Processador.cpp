#include <iostream>
#include <math.h>
#include <fstream>
#include <bitset>

#define dataBus 32
#define adressBus 16
#define numeroTotalEnderecos 64000
#define tamanhopalavra 4
#define tamanhoInstrucao 32
#define comecoMemoriaTexto 256
#define comecoMemoriaDados 3456
#define finalMemoriaDados 255999
#define numRegistradores 32

using namespace std;

#include "Conversor.cpp"
#include "If.cpp"
#include "Id.cpp"
#include "ExMem.cpp"
#include "Wb.cpp"

class Processador {

    private:
        Conversor *conversor;
        If *ifStage;
        //Id *idStage;
        //ExMem *exMemStage;
        //Wb *wbStage;
        int qtdClocks;
        void incrementarClock();

    public:
        Processador();
        ~Processador();
        void executar();
};

Processador::Processador() {

    conversor = new Conversor();
    //idStage = new Id();
    //exMemStage = new ExMem();
    //wbStage = new Wb();

    qtdClocks = 0;
}

Processador::~Processador() {

    delete conversor;
    delete ifStage;
    //delete idStage;
    //delete exMemStage;
    //delete wbStage;
}

void Processador::executar() {

    int PC = conversor->getEnderecoComecoMemmoriaTexto();
    Memoria *memoria = conversor->getMemoria();

    ifStage = new If(memoria, PC);

    cout << ifStage->getInstrucao() << endl;
    incrementarClock();
    cout << ifStage->getInstrucao() << endl;
    incrementarClock();

    cout << qtdClocks << endl;
}

void Processador::incrementarClock() {

    qtdClocks++;
}