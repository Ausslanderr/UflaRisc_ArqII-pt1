class Memoria {

    private:
        bitset<dataBus> *mem;
        int tamanhoMemoria;

    public:
        Memoria();
        ~Memoria();
        void armazenarInstrucao(string instrucaoAtual, int enderecoMemoriaTexto);
        void armazenarDado(string dado, int enderecoMemoriaDado);
        bitset<dataBus> getInstrucao(int posicao);
};

Memoria::Memoria() {

    tamanhoMemoria = pow(2, adressBus);

    mem = new bitset<dataBus>[tamanhoMemoria];
}

Memoria::~Memoria() {

    cout << "memoria morreu" << endl;

    delete[] mem;
}

void Memoria::armazenarInstrucao(string instrucaoAtual, int enderecoMemoriaTexto) {

    bitset<dataBus> instrucaoBitSet (instrucaoAtual);

    mem[enderecoMemoriaTexto] = instrucaoBitSet;
}

void Memoria::armazenarDado(string dado, int enderecoMemoriaDado) {

    bitset<dataBus> dadoBitSet (dado);

    mem[enderecoMemoriaDado] = dadoBitSet;
}

bitset<dataBus> Memoria::getInstrucao(int posicao) {

    if(posicao < 0 or posicao >= tamanhoMemoria) {

        throw(5);
    }

    return mem[posicao];
}
