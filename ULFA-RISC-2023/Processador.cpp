#define dataBus 32
#define adressBus 16
#define cout std::cout
#define endl std::endl

#include <math.h>

#include "Alu.cpp"
#include "ExMem.cpp"
#include "Id.cpp"
#include "If.cpp"
#include "Memoria.cpp"
#include "Registradores.cpp"
#include "Wb.cpp"
#include "Controle.cpp"
#include "Conversor.cpp"

class Processador {

    private:
        Alu *alu;
        ExMem *exMemStage;
        Id *idStage;
        If *ifStage;
        Memoria *memoria;
        Registradores *registrador;
        Wb *wbStage;
        Controle *controle;
        Conversor *conversor;

    public:
        Processador();
        ~Processador();
        void executar();
};

Processador::Processador() {

    alu = new Alu();
    exMemStage = new ExMem();
    idStage = new Id();
    ifStage = new If();
    memoria = new Memoria();
    registrador = new Registradores();
    wbStage = new Wb();
    controle = new Controle();
    conversor = new Conversor();
}

Processador::~Processador() {

    delete alu;
    delete exMemStage;
    delete idStage;
    delete ifStage;
    delete memoria;
    delete registrador;
    delete wbStage;
    delete controle;
    delete conversor;
}

void Processador::executar() {


}
