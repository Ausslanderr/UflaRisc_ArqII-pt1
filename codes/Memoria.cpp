class Memoria {

    private:
        bitset<dataBus> *mem;

    public:
        Memoria();
        ~Memoria();
        void armazenarInstrucao(string instrucaoAtual, int enderecoMemoriaTexto);
        void armazenarDado(bitset<dataBus> dado, bitset<addressBus> enderecoMemoriaDado);
        bitset<dataBus> getInstrucao(bitset<addressBus> posicao);
};

Memoria::Memoria() {

    mem = new bitset<dataBus>[tamanhoMemoria];
}

Memoria::~Memoria() {

    delete[] mem;

    cout << "memoria morreu" << endl;
}

void Memoria::armazenarInstrucao(string instrucaoAtual, int enderecoMemoriaTexto) {

    bitset<dataBus> instrucaoBitSet (instrucaoAtual);

    mem[enderecoMemoriaTexto] = instrucaoBitSet;
}

void Memoria::armazenarDado(bitset<dataBus> dado, bitset<addressBus> enderecoMemoriaDado) {

    int aux = (int)enderecoMemoriaDado.to_ulong();

    if(aux < limiteTamanhoMemoriaTexto or aux >= tamanhoMemoria) {

        throw(5);
    }
    
    mem[aux] = dado;

}

bitset<dataBus> Memoria::getInstrucao(bitset<addressBus> posicao) {

    int aux = (int)posicao.to_ulong();

    if(aux < 0 or aux >= tamanhoMemoria) {

        throw(5);
    }

    return mem[aux];
}
