#include <iostream>
#include <math.h>
#include <fstream>
#include <bitset>
#include <algorithm>
#include <vector>
#include <sstream>

#define dataBus 32
#define adressBus 16
#define numRegistradores 32
#define lengthRegister 8
#define c16 16 //const 16
#define c24 24 //const 24

using namespace std;

#include "Conversor.cpp"
#include "If.cpp"
#include "Id.cpp"
#include "ExMem.cpp"
#include "Wb.cpp"
#include "Controle.cpp"
#include "Registradores.cpp"

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

    try{
        conversor = new Conversor();
    }
    catch(int erro) {
        throw(erro);
    }
    
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

    try {
        int PC = conversor->getEnderecoComecoMemmoriaTexto();
        Memoria *memoria = conversor->getMemoria();

        ifStage = new If(memoria, PC);

        cout << ifStage->getInstrucao() << endl;
        incrementarClock();
        cout << ifStage->getInstrucao() << endl;
        incrementarClock();
        cout << ifStage->getInstrucao() << endl;
        incrementarClock();
        cout << ifStage->getInstrucao() << endl;
        incrementarClock();

        cout << "Bits da instrução atual: " << instrucaoAtual << endl;

        // Loop principal do processador
        while(!ifStage->ehInstrucaoFinal()) {

            // estágio id
            idStage = new Id(instrucaoAtual);
            incrementarClock();

            /*
            *   depuração id e controle (não é um estágio, apagar antes de entregar)
            *   decidi deletar o idStage para que os estágios ex/mem e wb 
            *   apenas possam fazer get dos atributos dessas classes 
            */
            idStage->depuracao();
            delete idStage;

            // estágio ex/mem
            exMemStage = new ExMem(idStage, ifStage);
            incrementarClock();

            // estágio wb
            // incrementarClock();

            // estágio if
            instrucaoAtual = ifStage->getInstrucao();
            incrementarClock();

            cout << "Bits da instrução atual: " << instrucaoAtual << endl;
        }

        cout << "Número de clocks do programa: " << qtdClocks << endl;
    }
    catch(int erro) {
        throw(erro);
    }
}

void Processador::incrementarClock() {

    qtdClocks++;
}