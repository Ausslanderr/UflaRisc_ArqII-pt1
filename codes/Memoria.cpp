class Memoria {

    private:
        bitset<dataBus> *mem;
        int tamanhoMemoria;

    public:
        Memoria();
        ~Memoria();
        void armazenarInstrucao(string instrucaoAtual, int enderecoMemoriaTexto);
        bitset<dataBus> getInstrucao(int posicao);
};

Memoria::Memoria() {

    tamanhoMemoria = pow(2, adressBus);

    mem = new bitset<dataBus>[tamanhoMemoria];
}

Memoria::~Memoria() {

    delete[] mem;
}

void Memoria::armazenarInstrucao(string instrucaoAtual, int enderecoMemoriaTexto) {

    bitset<dataBus> instrucaoBitSet (instrucaoAtual);

    mem[enderecoMemoriaTexto] = instrucaoBitSet;
}

bitset<dataBus> Memoria::getInstrucao(int posicao) {

    if(posicao < 0 or posicao >= tamanhoMemoria) {

        // FAZER ERRO
    }

    return mem[posicao];
}