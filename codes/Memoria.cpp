class Memoria {

    private:
        bitset<dataBus> *mem;

    public:
        Memoria();
        ~Memoria();
        void armazenarInstrucao(string instrucaoAtual, int enderecoMemoriaTexto);
        void armazenarDado(bitset<dataBus> dado, bitset<addressBus> enderecoMemoriaDado);
        bitset<dataBus> getInstrucao(bitset<addressBus> posicao);
        bitset<dataBus> getDado(bitset<dataBus> posicao);
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

    if(enderecoMemoriaTexto < 0 or enderecoMemoriaTexto >= limiteTamanhoMemoriaTexto) {

        throw(5);
    }

    mem[enderecoMemoriaTexto] = instrucaoBitSet;
}

void Memoria::armazenarDado(bitset<dataBus> dado, bitset<addressBus> enderecoMemoriaDado) {

    int aux = (int)enderecoMemoriaDado.to_ulong();

    if(aux < limiteTamanhoMemoriaTexto or aux >= tamanhoMemoria) {

        throw(5);
    }
    
    mem[aux] = dado;

    cout << "ARMAZENANDO DADO MEMORIA: " << mem[aux] << endl;
}

bitset<dataBus> Memoria::getInstrucao(bitset<addressBus> posicao) {

    int aux = (int)posicao.to_ulong();

    if(aux < 0 or aux >= limiteTamanhoMemoriaTexto) {

        throw(5);
    }

    return mem[aux];
}

bitset<dataBus> Memoria::getDado(bitset<dataBus> posicao) {

    int aux = (int)posicao.to_ulong();

    if(aux < limiteTamanhoMemoriaTexto or aux >= tamanhoMemoria) {

        throw(5);
    }

    return mem[aux];
}
