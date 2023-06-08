#include <thread>

using namespace std;

class Alu { 

    private:
        bitset<dataBus> rc, ra, rb, zero;
		bitset<addressBus> Const16, r31, PC;
		Id *idStage;
		If *ifStage;
		Registradores *reg;
		Controle *sinaisControle;
        bool ALUzero;
		bool overflow;
		bool carry;
        bool borrow;
		bool neg;
        void verificaNegativo(bitset<dataBus> rc);
		void verificaOverflow(bitset<dataBus> ra, string operacao);
        bitset<dataBus> calculaBits(bitset<dataBus> ra, bitset<dataBus> rb, string operacao);

    public:
        Alu(Id *idStage, Controle *sinaisControle, If *ifStage, Registradores *reg);
        void instrucoesAritmeticas();
        void instrucoesDeDesvio();
        void instrucoesDeMemoria();
        void mostrarFlags();
		void threadsDeImpressao(bitset<dataBus> ra, int i);
		bool getOverflow(){return overflow;};
		bitset<dataBus> getResultado(){return rc;};
		bitset<addressBus> getRetornoFuncao(){return r31;};
		//void resetFlagsDesvio(); Isso vai ser necessario, mesmo possuindo o construtor?
        
};

Alu::Alu(Id *idStage, Controle *sinaisControle, If *ifStage, Registradores *reg) {

	this->idStage = idStage;
	this->sinaisControle = sinaisControle;
	this->ifStage = ifStage;
	this->reg = reg;

	PC = ifStage->getPc();
	rc = idStage->getRcValue();
	ra = idStage->getRaValue();
	rb = idStage->getRbValue();
	r31 = reg->getRegistrador(31);
	Const16 = idStage->getConst16();
	
    //address = ???
    //end = ???

    ALUzero = 0;
    zero = 0;
    overflow = 0;
	carry = 0;
    borrow = 0;
	neg = 0;
}

void Alu::instrucoesAritmeticas(){

	bool aux = 0;
	
	// SOMA INTEIRA
	if(sinaisControle->getAluctrl() == "add"){
		rc = calculaBits(ra, rb, "adicao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de add" << endl << endl;
	}
	
	// SUBTRAÇÃO INTEIRA
	if(sinaisControle->getAluctrl() == "sub"){
		rc = calculaBits(ra, rb, "subtracao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de sub" << endl << endl;
	}
	
	// ZERA
	if(sinaisControle->getAluctrl() == "zeros"){
		rc = 0;
		// nao causa overflow
		// neg por padrao é zero
		zero = rc;
		
		cout << "Eh uma instrucao de zeros" << endl << endl;
	}
	
	// XOR LÓGICO
	if(sinaisControle->getAluctrl() == "xor"){
		rc = ra ^ rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;

		cout << "Eh uma instrucao de xor" << endl << endl;
	}
	
	// OR LÓGICO
	if(sinaisControle->getAluctrl() == "or"){
		rc = ra | rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de or" << endl << endl;
	}
	
	// NOT
	if(sinaisControle->getAluctrl() == "passnota"){
		rc = ~ra;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de passnota" << endl << endl;
	}
	
	// AND LÓGICO
	if(sinaisControle->getAluctrl() == "and"){
		rc = ra & rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de and" << endl << endl;
	}
	
	// SHIFT ARITMÉTICO PARA A ESQUERDA
	if(sinaisControle->getAluctrl() == "asl"){
		aux = ra[31]; 
		rc = ra << rb;
		rc[31] = aux;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de asl" << endl << endl;
	}
	
	// SHIFT ARITMÉTICO PARA A DIREITA
	if(sinaisControle->getAluctrl() == "asr"){
		aux = ra[31]; 
		rc = ra >> rb;
		rc[31] = aux;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de asr" << endl << endl;
	}

	// SHIFT LÓGICO PARA A ESQUERDA
	if(sinaisControle->getAluctrl() == "lsl"){
		rc = ra << rb;
		rc[31] = aux;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lsl" << endl << endl;
	}
	
	// SHIFT LÓGICO PARA A DIREITA
	if(sinaisControle->getAluctrl() == "lsr"){
		rc = ra >> rb;
		rc[31] = aux;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lsr" << endl << endl;
	}
	
	// COPIA
	if(sinaisControle->getAluctrl() == "passa"){
		rc = ra;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de passa" << endl << endl;
	}
	
	// CARREGA CONSTANTE NOS 2 BYTES MAIS SIGNIFICATIVOS
	if(sinaisControle->getAluctrl() == "lch"){
		rc = (Const16 << 16) | (rc & 0x0000ffff);
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lch" << endl << endl;
	}
	
	// CARREGA CONSTANTE NOS 2 BYTES MENOS SIGNIFICATIVOS
	if(sinaisControle->getAluctrl() == "lcl"){
		rc = Const16 | (rc & 0x0000ffff);
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lcl" << endl << endl;
	}

	// Slt
	if(sinaisControle->getAluctrl() == "slt"){
		rc = ra < rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de slt" << endl << endl;
	}

	// Slti
	if (sinaisControle->getAluctrl() == "slti") {

 		//rc = ra < valor_offset_address;
    	// não causa overflow
    	verificaNegativo(rc);
    	zero = rc;

    	cout << "Eh uma instrucao de slti" << endl << endl;
	}

	// Smt
	if (sinaisControle->getAluctrl() == "smt") {

		const int numThreads = 2;
    	thread threads[numThreads];

    	// Cria as threads e inicia sua execução
    	for (int i = 0; i < numThreads; ++i) {
        	threads[i] = thread(threadsDeImpressao, ra, i);
    	}

    	// Aguarda a conclusão de todas as threads
    	for (int i = 0; i < numThreads; ++i) {
        	threads[i].join();
    	}
 		
    	// não causa overflow
    	// não causa neg
    	zero = ra;

    	cout << "Eh uma instrucao de smt" << endl << endl;
	}

	// Inc
	if (sinaisControle->getAluctrl() == "inc") {

 		rc = calculaBits(rc, 1, "adicao");
    	verificaNegativo(rc);
    	zero = rc;

    	cout << "Eh uma instrucao de inc" << endl << endl;
	}

	// Dec
	if (sinaisControle->getAluctrl() == "dec") {

 		rc = calculaBits(rc, 1, "subtracao");
    	verificaNegativo(rc);
    	zero = rc;

    	cout << "Eh uma instrucao de dec" << endl << endl;
	}

	// Addi
	if(sinaisControle->getAluctrl() == "addi"){
		//rc = ra + valor_offset_address;
		//verifica_overflow(rc, ra, valor_offset_address, "adicao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de addi" << endl << endl;
	}

	// Subi
	if(sinaisControle->getAluctrl() == "subi"){
		//rc = ra - valor_offset_address;
		//verifica_overflow(rc, ra, valor_offset_address, "subtracao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de subi" << endl << endl;
	}

	// Nand
	if (sinaisControle->getAluctrl() == "nand") {
    	rc = ~(ra & rb);
    	// não causa overflow
    	verificaNegativo(rc);
    	zero = rc;

    	cout << "Eh uma instrucao de nand" << endl << endl;
	}

	// Nor
	if(sinaisControle->getAluctrl() == "nor"){
		rc = ~(ra | rb);
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de nor" << endl << endl;
	}
	
	// Verifica se algum resultado corresponde a 0 para acionar a flag
	if(zero == 0){
		ALUzero = 1;
	}
}

void Alu::instrucoesDeDesvio(){

	// JUMP AND LINK
	if(sinaisControle->getAluctrl() == "jal"){
		r31 = PC; 
		PC = end;	
		cout << "Eh uma instrucao de jal" << endl << endl;
	}
	
	// JUMP REGISTER
	if(sinaisControle->getAluctrl() == "jr"){
		PC = r31;	
		cout << "Eh uma instrucao de jr" << endl << endl;
	}
	
	//  JUMP SE IGUAL (BEQ)
	if(sinaisControle->getAluctrl() == "beq"){
		PC = end; //tenho que tratar se j foi tomado (fazer um if)
		cout << "Eh uma instrucao de beq" << endl << endl;
	}
	
	//  JUMP SE DIFERENTE (BNE)
	if(sinaisControle->getAluctrl() == "bne"){
		PC = end; //tenho que tratar se j foi tomado (fazer um if)
		cout << "Eh uma instrucao de bne" << endl << endl;
	}
	
	//  JUMP INCONDICIONAL
	if(sinaisControle->getAluctrl() == "j"){
		PC = adress;
		cout << "Eh uma instrucao de j" << endl << endl;
	}
	
	// Alterar o PC e o r31 já que eles foram modificados
	ifStage->desviaPc(PC);
	reg->setRegistrador(r31, 31);
	
}

void Alu::instrucoesDeMemoria(){
	
	// LOAD WORD (vou refazer)
	if(sinaisControle->getAluctrl() == "load"){
		rc = memória[ra];
		cout << "Eh uma instrucao de load" << endl << endl;
	}
	
	// STORE WORD (vou refazer)
	if(sinaisControle->getAluctrl() == "store"){
		memória[rc] = ra;
		cout << "Eh uma instrucao de store" << endl << endl;
	}
}

bitset<dataBus> Alu::calculaBits(bitset<dataBus> ra, bitset<dataBus> rb, string operacao){
	
	// adicao
	if((operacao == "adicao")){
		
        bitset<dataBus> sum;
	
		for (int i = 0; i < dataBus; i++) {
			sum[i] = ra[i] ^ rb[i] ^ carry;  // Soma bit a bit com carry
			carry = (ra[i] & rb[i]) | (carry & (ra[i] ^ rb[i]));  // Calcula o carry para o próximo bit
		}

		verificaOverflow(ra, operacao);
        return sum;
    }
		
	// subtracao
	if((operacao == "subtracao")){
		bitset<dataBus> difference;
		
		for (int i = 0; i < dataBus; i++) {
			difference[i] = ra[i] ^ rb[i] ^ borrow;  // Subtrai bit a bit com borrow
			borrow = (!ra[i] & rb[i]) | (borrow & (ra[i] ^ rb[i]));  // Calcula o borrow para o próximo bit
		}

		verificaOverflow(ra, operacao);
        return difference;
    }

    return 0;
			
}

void Alu::verificaOverflow(bitset<dataBus> ra, string operacao){

	if(operacao == "adicao"){
		overflow = carry;
	}
	
	if(operacao == "subtracao"){
		overflow = (borrow != ra[31]);
	}

}

void Alu::verificaNegativo(bitset<dataBus> rc){

	// Verifica se o bit mais significativo é 1 (Se é negativo)
	if (rc[31]) {
        neg = 1;
    }

}

void::threadsDeImpressao(bitset<dataBus> ra, int i){
	cout<<"Testando Thread " << i << " com o valor de Ra: " << ra << endl; 
}

void Alu::mostrarFlags(){
	
	cout << "Flags da ALU e endereco de desvio: " << endl;
	cout << "\tFlag de Zero: " << ALUzero << endl;
    cout << "\tCarry: " << carry << endl;
    cout << "\tNegativo: " << neg << endl;
	cout << "\tSinal de Overflow: " << overflow << endl;
	cout << "\tCalculo do endereco de desvio (valor de resultado): " << rc << endl;
}

/*
void ExMem::resetFlagsDesvio(){
	
	ALUzero = 0;
	Overflow = 0;
	resultado_endereco = 0;
	HI = LO = resultado_ALU = 0;
	valor_novo_ra = valor_novo_PC = 0;
}
*/
