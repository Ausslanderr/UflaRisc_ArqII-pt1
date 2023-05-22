class Memoria {

    private:
        std::bitset<dataBus> *mem;
        int tamanhoMemoria;

    public:
        Memoria();
        ~Memoria();
};

Memoria::Memoria() {

    tamanhoMemoria = pow(2, adressBus);

    mem = new std::bitset<dataBus>[tamanhoMemoria];
}

Memoria::~Memoria() {

    delete[] mem;
}
