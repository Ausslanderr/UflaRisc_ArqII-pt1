class Memoria {

    private:
        bitset<dataBus> *mem;

    public:
        Memoria();
        ~Memoria();
        void armazenarInstrucao(string instrucaoAtual, int enderecoMemoriaTexto);
        void armazenarDado(string dado, int enderecoMemoriaDado);
        bitset<dataBus> getInstrucao(bitset<addressBus> posicao);
};

Memoria::Memoria() {

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

bitset<dataBus> Memoria::getInstrucao(bitset<addressBus> posicao) {

    int aux = (int)posicao.to_ulong();

    if(aux < 0 or aux >= tamanhoMemoria) {

        throw(5);
    }

    return mem[aux];
}
