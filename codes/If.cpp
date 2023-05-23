class If {

    private:
        int PC;
        bitset<dataBus> registradorInstrucoes;
        Memoria *memoria;

    public:
        If(Memoria *memoria, int PC);
        ~If();
        bitset<dataBus> getInstrucao();
};

If::If(Memoria *memoria, int PC) {

    this->memoria = memoria;
    this->PC = PC;
}

If::~If() {


}

bitset<dataBus> If::getInstrucao(){

    registradorInstrucoes = memoria->getInstrucao(PC);
    PC++;

    return registradorInstrucoes;
}
