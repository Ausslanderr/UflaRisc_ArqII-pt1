#include <iostream>
#include "codes/Processador.cpp"

int main() {

    Processador *uflaRisc = new Processador();

    uflaRisc->executar();

    delete uflaRisc;

    return 0;
}