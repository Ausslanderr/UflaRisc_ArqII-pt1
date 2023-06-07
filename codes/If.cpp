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
        bitset<16> getPc();
        void desviaPc(bitset<16> PC);
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

bool If::ehInstrucaoFinal() {

    bitset<dataBus> comparacao ("11111111111111111111111111111111");

    if(registradorInstrucoes == comparacao) {
        return true;
    }
    return false;
}

bitset<16> If::getPc(){
    return PC;
} 

void If::desviaPc(bitset<16> PC){
    this->PC = PC;
}