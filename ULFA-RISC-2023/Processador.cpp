#include "Alu.cpp"
#include "ExMem.cpp"
#include "Id.cpp"
#include "If.cpp"
#include "Memoria.cpp"
#include "Registradores.cpp"
#include "Wb.cpp"

class Processador {

    private:
        Alu *alu;
        ExMem *exMemStage;
        Id *idStage;
        If *ifStage;
        Memoria *memoria;
        Registradores *registrador;
        Wb *wbStage;

    public:
        Processador();
        ~Processador();
};

Processador::Processador() {

    alu = new Alu();
    exMemStage = new ExMem();
    idStage = new Id();
    ifStage = new If();
    memoria = new Memoria();
    registrador = new Registradores();
    wbStage = new Wb();
}

Processador::~Processador() {

    delete alu;
    delete exMemStage;
    delete idStage;
    delete ifStage;
    delete memoria;
    delete registrador;
    delete wbStage;
}
