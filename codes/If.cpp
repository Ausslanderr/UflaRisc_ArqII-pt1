class If {

    private:
        bitset<addressBus> PC;
        bitset<dataBus> registradorInstrucoes;
        Memoria *memoria;
        void adicionarPc();

    public:
        If(Memoria *memoria, bitset<addressBus> PC);
        ~If();
        bitset<dataBus> getInstrucao();
        bitset<addressBus> getPc();
        void desviaPc(bitset<addressBus> PC);
        bool ehInstrucaoFinal();
};

If::If(Memoria *memoria, bitset<addressBus> PC) {

    this->memoria = memoria;
    this->PC = PC;
}

If::~If() {

    cout << "If morreu" << endl;
}

bitset<dataBus> If::getInstrucao(){

    try {
        registradorInstrucoes = memoria->getInstrucao(PC);
        adicionarPc();
    }
    catch(int erro) {
        throw(erro);
    }

    return registradorInstrucoes;
}

void If::adicionarPc() {

    bool carry;
	bitset<addressBus> inc(1);
	bitset<addressBus> sum;
	
	for(int i = 0; i < addressBus; i++) {
		
		sum[i] = PC[i] ^ inc[i] ^ carry;  // Soma bit a bit com carry
		carry = (PC[i] & inc[i]) | (carry & (PC[i] ^ inc[i]));  // Calcula o carry para o próximo bit
	}

    PC = sum;
	
	cout << "Valor atual do PC: " << PC << endl;
}

bitset<addressBus> If::getPc(){
    return PC;
} 

void If::desviaPc(bitset<addressBus> PC){
    this->PC = PC;
}
