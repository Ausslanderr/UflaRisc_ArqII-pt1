#include <bitset>

class Memoria {

    private:
        std::bitset<dataBus> *mem;
        int tamanhoMemoria;

    public:
        Memoria();
        ~Memoria();
        void testarMemoria();
};

Memoria::Memoria() {

    tamanhoMemoria = pow(2, adressBus);

    mem = new std::bitset<dataBus>[tamanhoMemoria];

    testarMemoria();
}

Memoria::~Memoria() {

    delete[] mem;
}

void Memoria::testarMemoria() {

    mem[0].set(2);
    mem[65535].set(4);

    cout << mem[0] << endl;
    cout << mem[1] << endl;
    cout << mem[65535] << endl;
}
