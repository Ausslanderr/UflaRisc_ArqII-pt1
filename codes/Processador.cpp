#include <iostream>
#include <math.h>
#include <fstream>
#include <bitset>
#include <algorithm>
#include <vector>
#include <sstream>

#define dataBus 32
#define addressBus 16
#define tamanhoMemoria 65536
#define limiteTamanhoMemoriaTexto 16384
#define numRegistradores 32
#define lengthRegister 8
#define c16 16 //const 16
#define c24 24 //const 24

using namespace std;

#include "Conversor.cpp"
#include "Registradores.cpp"
#include "If.cpp"
#include "Id.cpp"
#include "ExMem.cpp"
#include "Wb.cpp"

class Processador {

    private:
        Conversor *conversor;
        Registradores *regs;
        If *ifStage;
        Id *idStage;
        ExMem *exMemStage;
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
        regs = new Registradores();
    }
    catch(int erro) {
        throw(erro);
    }
    
    //exMemStage = new ExMem();
    //wbStage = new Wb();

    qtdClocks = 0;
}

Processador::~Processador() {

    cout << "processador morreu" << endl;

    delete conversor;
    delete regs;
    delete ifStage;
    //delete exMemStage;
    //delete wbStage;
}

void Processador::executar() {

    try {
        bitset<addressBus> PC (conversor->getEnderecoComecoMemmoriaTexto());
        Memoria *memoria = conversor->getMemoria();
        ifStage = new If(memoria, PC);

        // estágio if inicial
        bitset<dataBus> instrucaoAtual = ifStage->getInstrucao();
        incrementarClock();

        cout << "Bits da instrução atual: " << instrucaoAtual << endl;

        // Loop principal do processador
        while(!ifStage->ehInstrucaoFinal()) {

            // estágio id
            idStage = new Id(instrucaoAtual, regs);
            incrementarClock();

            /*
            *   depuração id e controle (não é um estágio, apagar antes de entregar)
            *   decidi deletar o idStage para que os estágios ex/mem e wb 
            *   apenas possam fazer get dos atributos dessas classes 
            */
            idStage->depuracao();
            delete idStage;

            // estágio ex/mem
            exMemStage = new ExMem(idStage, idStage->getControle(), ifStage, regs);
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
