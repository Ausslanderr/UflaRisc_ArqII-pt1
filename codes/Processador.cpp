#include <math.h>
#include <fstream>
#include <bitset>

#define dataBus 32
#define adressBus 16

using namespace std;

#include "Alu.cpp"
#include "ExMem.cpp"
#include "Id.cpp"
#include "If.cpp"
#include "Memoria.cpp"
#include "Registradores.cpp"
#include "Wb.cpp"
#include "Controle.cpp"

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
}

void Processador::executar() {

    string nome_arquivo_entrada;

    cout << "Digite o nome do arquivo de entrada de instruções (sem extensão): ";
	cin >> nome_arquivo_entrada;

    do {

        ifStage->executar(nome_arquivo_entrada);

        cout << ifStage->getInstrucao() << endl;

    } while(ifStage->getInstrucao() != "11111111111111111111111111111111");
}
