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
#define c8 8 //const 8
#define c16 16 //const 16
#define c24 24 //const 24

using namespace std;

// converte um binario para inteiro (considera o sinal)
long conversorBinInteiro(bitset<dataBus> bin) {

    long resultado = 0;
    long potencia = 1;
    bool ehNeg = false;

   // negativo
    if(bin[dataBus - 1] == 1) {

        ehNeg = true;

        // invertido
        bitset<32> invertido = ~bin;

        // invertido + 1
        bool carry;
	    bitset<dataBus> inc(1);
	    bitset<dataBus> sum;
	
	    for(int i = 0; i < dataBus; i++) {
		
		    sum[i] = invertido[i] ^ inc[i] ^ carry;
		    carry = (invertido[i] & inc[i]) | (carry & (invertido[i] ^ inc[i]));
	    }

        bin = sum;
    }

    // conversão
    for(int i = 0; i <= dataBus - 1; i++) {

        if(bin[i] == 1) {
            resultado += potencia;
        }

        potencia *= 2;
    }

    if(ehNeg) {
        resultado *= -1;
    }

    return resultado;
}

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
        Wb *wbStage;
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

    qtdClocks = 0;
}

Processador::~Processador() {

    delete conversor;
    delete regs;
}

void Processador::executar() {

    bool processando = true;

    try {
        bitset<addressBus> PC (conversor->getEnderecoComecoMemmoriaTexto());
        Memoria *memoria = conversor->getMemoria();
        ifStage = new If(memoria, PC);

        cin.ignore();

        // Loop principal do processador
        while(processando) {

            // estágio if
            bitset<dataBus> instrucaoAtual = ifStage->getInstrucao();
            incrementarClock();

            cout << "Bits da instrução atual: " << instrucaoAtual << endl;

            regs->depuracao();

            // estágio id
            idStage = new Id(instrucaoAtual, regs);
            idStage->depuracao();
            incrementarClock();

            // estágio ex/mem
            exMemStage = new ExMem(regs, ifStage, idStage, idStage->getControle(), memoria);
            processando = exMemStage->getAlu()->getHalt();
            exMemStage->getAlu()->mostrarFlags();
            incrementarClock();

            // estágio wb
            wbStage = new Wb(regs, idStage, idStage->getControle(), exMemStage->getAlu(), memoria);
            incrementarClock();

            delete idStage;
            delete exMemStage;
            delete wbStage;

            cout << endl << "#########################################################################" << endl << endl;

            cout << "Pressione ENTER para a próxima instrução . . . ";
            cin.get();
        }

        delete ifStage;

        cout << "Número de clocks do programa: " << qtdClocks << endl;
    }
    catch(int erro) {
        throw(erro);
    }
}

void Processador::incrementarClock() {

    qtdClocks++;
}
