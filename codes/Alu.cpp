class Alu { 

    private:
		bitset<dataBus> PC, Const8, Const16, Const24, rc, ra, rb, r31, num, zero;
		bitset<addressBus> novoPC, novoRc;
		Registradores *regs;
		If *ifStage;
		Id *idStage;
		Controle *controle;
		Memoria *memoria;
        bool ALUzero;
		bool overflow;
		bool carry;
        bool borrow;
		bool neg;
		bool continuar;
        void verificaNegativo(bitset<dataBus> rc);
		void verificaOverflow(bitset<dataBus> ra, bitset<dataBus> rb, bitset<dataBus> result, string operacao);
		void converteBits(int operacao);
        bitset<dataBus> calculaBits(bitset<dataBus> ra, bitset<dataBus> rb, string operacao);

    public:
        Alu(Registradores *regs, If *ifStage, Id *idStage, Controle *controle, Memoria *memoria);
		~Alu();
        void instrucoesAritmeticas();
        void instrucoesDeDesvio();
        void instrucoesDeMemoria();
        void mostrarFlags();
		bool getOverflow()					{return overflow;};
		bitset<dataBus> getResultadoRa()	{return ra;};
		bitset<dataBus> getResultadoRc()	{return rc;};
		bitset<dataBus> getRetornoFuncao()	{return r31;};
		bool getHalt()						{return continuar;};
        
};

Alu::Alu(Registradores *regs, If *ifStage, Id *idStage, Controle *controle, Memoria *memoria) {

	this->regs = regs;
	this->ifStage = ifStage;
	this->idStage = idStage;
	this->controle = controle;
	this->memoria = memoria;
	
	rc = idStage->getRcValue();
	ra = idStage->getRaValue();
	rb = idStage->getRbValue();
	r31 = regs->getRegistrador(31);
	
	converteBits(1);

    ALUzero = 0;
    zero = 0;
    overflow = 0;
	carry = 0;
    borrow = 0;
	neg = 0;
	num = (65535);
	continuar = true;
}

Alu::~Alu() {

	cout << "alu morreu" << endl;
}

void Alu::instrucoesAritmeticas() {

	bool aux = 0;
	
	// SOMA INTEIRA
	if(controle->getAluctrl() == "add") {
		rc = calculaBits(ra, rb, "adicao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de add" << endl << endl;
	}
	
	// SUBTRAÇÃO INTEIRA
	else if(controle->getAluctrl() == "sub") {
		rc = calculaBits(ra, rb, "subtracao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de sub" << endl << endl;
	}
	
	// ZERA
	else if(controle->getAluctrl() == "zeros") {
		rc = 0;
		// nao causa overflow
		// neg por padrao é zero
		zero = rc;
		
		cout << "Eh uma instrucao de zeros" << endl << endl;
	}
	
	// XOR LÓGICO
	else if(controle->getAluctrl() == "xor") {
		rc = ra ^ rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;

		cout << "Eh uma instrucao de xor" << endl << endl;
	}
	
	// OR LÓGICO
	else if(controle->getAluctrl() == "or") {
		rc = ra | rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de or" << endl << endl;
	}
	
	// NOT
	else if(controle->getAluctrl() == "passnota") {
		rc = ~ra;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de passnota" << endl << endl;
	}
	
	// AND LÓGICO
	else if(controle->getAluctrl() == "and") {
		rc = ra & rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de and" << endl << endl;
	}
	
	// SHIFT ARITMÉTICO PARA A ESQUERDA
	else if(controle->getAluctrl() == "asl" ){
		aux = ra[31]; 
		rc = ra << rb.to_ulong();
		rc[31] = aux;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de asl" << endl << endl;
	}
	
	// SHIFT ARITMÉTICO PARA A DIREITA
	else if(controle->getAluctrl() == "asr") {
		aux = ra[31]; 
		rc = ra >> rb.to_ulong();
		rc[31] = aux;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de asr" << endl << endl;
	}

	// SHIFT LÓGICO PARA A ESQUERDA
	else if(controle->getAluctrl() == "lsl") {
		rc = ra << rb.to_ulong();
		rc[31] = aux;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lsl" << endl << endl;
	}
	
	// SHIFT LÓGICO PARA A DIREITA
	else if(controle->getAluctrl() == "lsr") {
		rc = ra >> rb.to_ulong();
		rc[31] = aux;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lsr" << endl << endl;
	}
	
	// COPIA
	else if(controle->getAluctrl() == "passa") {
		rc = ra;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de passa" << endl << endl;
	}
	
	// CARREGA CONSTANTE NOS 2 BYTES MAIS SIGNIFICATIVOS
	else if(controle->getAluctrl() == "lch") {
		rc = (Const16 << 16) | (rc & num);
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lch" << endl << endl;
	}
	
	// CARREGA CONSTANTE NOS 2 BYTES MENOS SIGNIFICATIVOS
	else if(controle->getAluctrl() == "lcl") {
		rc = Const16 | (rc & num);
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lcl" << endl << endl;
	}

	// Slt
	else if(controle->getAluctrl() == "slt") {
		
	    bool result = false; 
		rc = result;

    	for (int i = 31; i >= 0 && !result ; i--) {
    		if (ra[i] < rb[i]) {
				result = 1;
        		rc = result;
        	} 
			else if (ra[i] > rb[i]) {
				break;
        	}
    	}

		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de slt" << endl << endl;
	}

	// Slti
	else if(controle->getAluctrl() == "slti") {

		bool result = false;
		rc = result;

    	for (int i = 31; i >= 0 && !result ; i--) {
    		if (rb[i] < Const8[i]) {
        		result = 1;
        		rc = result;
        	} 
			else if (rb[i] > Const8[i]) {
            	break;
        	}
    	}

    	// não causa overflow
    	verificaNegativo(rc);
    	zero = rc;

    	cout << "Eh uma instrucao de slti" << endl << endl;
	}

	// Smt
	else if(controle->getAluctrl() == "smt") {

		bool result = false; 
		rc = result;

    	for (int i = 31; i >= 0 && !result ; i--) {
    		if (ra[i] > rb[i]) {
				result = 1;
        		rc = result;
        	} 
			else if (ra[i] < rb[i]) {
				break;
        	}
    	}

    	cout << "Eh uma instrucao de smt" << endl << endl;
	}

	// Inc
	else if(controle->getAluctrl() == "inc"){

 		rc = calculaBits(rc, 1, "adicao");
    	verificaNegativo(rc);
    	zero = rc;

    	cout << "Eh uma instrucao de inc" << endl << endl;
	}

	// Dec
	else if(controle->getAluctrl() == "dec") {

 		rc = calculaBits(rc, 1, "subtracao");
    	verificaNegativo(rc);
    	zero = rc;

    	cout << "Eh uma instrucao de dec" << endl << endl;
	}

	// Addi
	else if(controle->getAluctrl() == "addi") {
		rc = calculaBits(rb, Const8, "adicao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de addi" << endl << endl;
	}

	// Subi
	else if(controle->getAluctrl() == "subi") {
		rc = calculaBits(rb, Const8, "subtracao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de subi" << endl << endl;
	}

	// Nand
	else if(controle->getAluctrl() == "nand") {

		bool comeco = false;

		for (int i = 31; i >= 0; i--) {

			if(!comeco and ra[i] == 0 and rb[i] == 0) {
				continue;
			}
			else {
				comeco = true;
				if((ra[i] & rb[i]) == 0) {
					rc[i] = 1;
				}
				else {
					rc[i] = 0;
				}
			}
    	}
    	// não causa overflow
    	verificaNegativo(rc);
    	zero = rc;

    	cout << "Eh uma instrucao de nand" << endl << endl;
	}

	// Nor
	else if(controle->getAluctrl() == "nor") {
		
		bool comeco = false;

		for (int i = 31; i >= 0; i--) {

			if(!comeco and ra[i] == 0 and rb[i] == 0) {
				continue;
			}
			else {
				comeco = true;
				if((ra[i] | rb[i]) == 1) {
					rc[i] = 0;
				}
				else {
					rc[i] = 1;
				}
			}
    	}
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de nor" << endl << endl;
	}

	// halt
	else if(controle->getAluctrl() == "halt - saída de sistema") {
		continuar = false;

		cout << "Eh uma instrucao de halt" << endl << endl;
	}
	
	// Verifica se algum resultado corresponde a 0 para acionar a flag
	if(zero == 0) {
		ALUzero = 1;
	}
}

void Alu::instrucoesDeDesvio() {

	// JUMP AND LINK
	if(controle->getAluctrl() == "jal") {
		r31 = PC;
		PC = Const24;
		cout << "Eh uma instrucao de jal" << endl << endl;
	}
	
	// JUMP REGISTER
	else if(controle->getAluctrl() == "jr") {
		PC = r31;	
		cout << "Eh uma instrucao de jr" << endl << endl;
	}
	
	//  JUMP SE IGUAL (BEQ)
	else if(controle->getAluctrl() == "beq") {
		if(ra == rb)
			PC = Const8;

		cout << "Eh uma instrucao de beq" << endl << endl;
	}
	
	//  JUMP SE DIFERENTE (BNE)
	else if(controle->getAluctrl() == "bne") {
		if(ra != rb){
			PC = Const8;
		}

		cout << "Eh uma instrucao de bne" << endl << endl;
	}
	
	//  JUMP INCONDICIONAL
	else if(controle->getAluctrl() == "j") {
		PC = Const24;
		cout << "Eh uma instrucao de j" << endl << endl;
	}
	
	// Altera o PC e o r31 já que eles foram modificados.
	converteBits(2);
	ifStage->desviaPc(novoPC);
	regs->setRegistrador(r31, 31);
}

void Alu::instrucoesDeMemoria() {
	
	// LOAD WORD (vou refazer)
	if(controle->getAluctrl() == "load"){
		//rc = tenho que setar na memoria o ra;
		cout << "Eh uma instrucao de load" << endl << endl;
	}
	
	// STORE WORD (vou refazer)
	if(controle->getAluctrl() == "store"){

		if (controle->getRegwrite() == 0  && controle->getMemwrite() == 1){

			converteBits(3);

			memoria->armazenarDado(ra, novoRc);

			cout << "Eh uma instrucao de store" << endl << endl;
			
		}
	}
}

void Alu::converteBits(int operacao) {

	if(operacao == 1){ // Converte para 32

    	bitset<addressBus> PC = ifStage->getPc();

		bitset<c8>  Const8 =  idStage->getConst8();
    	bitset<c16> Const16 = idStage->getConst16();
    	bitset<c24> Const24 = idStage->getConst24();

    	for (int i = 0; i < addressBus; i++) {
        	this->PC[i] = PC[i];
    	}

		// const8 (do id) é negativo
		if(Const8[c8 - 1] == 1) {
			for(int i = dataBus - 1; i > 0; i--) {
				this->Const8[i] = 1;
			}
		}
		// const8 (da alu) recebe os bits do const8 (do id)
		for (int i = 0; i < 8; i++) {
        	this->Const8[i] = Const8[i];
    	}

		// const16 (do id) é negativo
		if(Const16[c16 - 1] == 1) {
			for(int i = dataBus - 1; i > 0; i--) {
				this->Const16[i] = 1;
			}
		}
		// const16 (da alu) recebe os bits do const16 (do id)
    	for (int i = 0; i < c16; i++) {
        	this->Const16[i] = Const16[i];
    	}

		// const24 (do id) é negativo
		if(Const24[c24 - 1] == 1) {
			for(int i = dataBus - 1; i > 0; i--) {
				this->Const24[i] = 1;
			}
		}
		// const24 (da alu) recebe os bits do const24 (do id)
		for (int i = 0; i < c24; i++) {
        	this->Const24[i] = Const24[i];
    	}
	}

	else if(operacao == 2){ // Converte de 32 para 16 (PC)
		
		for (int i = 0; i < addressBus; i++) {
        	novoPC[i] = this->PC[i];
    	}

	}

	else if(operacao == 3){	// Converte de 32 para 16 (Rc ao realizar a instrução store)

		for (int i = 0; i < addressBus; i++) {
        	novoRc[i] = rc[i];
    	}

	}

}

bitset<dataBus> Alu::calculaBits(bitset<dataBus> ra, bitset<dataBus> rb, string operacao) {

    // adicao
    if((operacao == "adicao")) {

        bitset<dataBus> sum;

        for (int i = 0; i < dataBus - 1; i++) {
            sum[i] = ra[i] ^ rb[i] ^ carry;  // Soma bit a bit com carry
            carry = (ra[i] & rb[i]) | (carry & (ra[i] ^ rb[i]));  // Calcula o carry para o próximo bit
        }

		// converte o binario para um inteiro (considerendo o sinal)
		long result = conversorBinInteiro(ra) + conversorBinInteiro(rb);

        if (result < 0) {
            for(int i = 31; i > 0; i--){
                if(sum[i] == 0){
                    sum[i] = 1;
                }
                else if(sum[i] == 1){
                    i = 0;
                }
            }
        }

        verificaOverflow(ra, rb, sum, operacao);
        return sum;
    }

    // subtracao
    if((operacao == "subtracao")){
        bitset<dataBus> difference;

        for (int i = 0; i < dataBus - 1; i++) {
            difference[i] = ra[i] ^ rb[i] ^ borrow;  // Subtrai bit a bit com borrow
            borrow = (!ra[i] & rb[i]) | ((borrow & !ra[i]) & !(ra[i] ^ rb[i]));  // Calcula o borrow para o próximo bit
        }

		// converte o binario para um inteiro (considerendo o sinal)
		long result = conversorBinInteiro(ra) - conversorBinInteiro(rb);

        if (result < 0) {
            for(int i = 31; i > 0; i--){
                if(difference[i] == 0){
                    difference[i] = 1;
                }
                else if(difference[i] == 1){
                    i = 0;
                }
            }
        }

        verificaOverflow(ra, rb, difference, operacao);
        return difference;
    }

    return 0;
}

void Alu::verificaOverflow(bitset<dataBus> ra, bitset<dataBus> rb, bitset<dataBus> result, string operacao) {

	if(operacao == "adicao"){
		if(conversorBinInteiro(ra) >= 0 and conversorBinInteiro(rb) >= 0 and conversorBinInteiro(result) < 0) {
			overflow = true;
		}

		else if(conversorBinInteiro(ra) < 0 and conversorBinInteiro(rb) < 0 and conversorBinInteiro(result) >= 0) {
			overflow = true;
		}
	}
	
	else if(operacao == "subtracao"){
		if(conversorBinInteiro(ra) >= 0 and conversorBinInteiro(rb) < 0 and conversorBinInteiro(result) < 0) {
			overflow = true;
		}

		else if(conversorBinInteiro(ra) < 0 and conversorBinInteiro(rb) >= 0 and conversorBinInteiro(result) >= 0) {
			overflow = true;
		}
	}

	if(overflow) {
		throw(12);
	}

}

void Alu::verificaNegativo(bitset<dataBus> rc) {

	// Verifica se o bit mais significativo é 1 (Se é negativo)
	if (rc[31]) {
        neg = 1;
    }

}

void Alu::mostrarFlags() {
	
	cout << "Flags da ALU e endereco de desvio: " << endl;
	cout << "\tFlag de Zero: "		<< ALUzero << endl;
    cout << "\tCarry: " 			<< carry << endl;
    cout << "\tNegativo: " 			<< neg << endl;
	cout << "\tSinal de Overflow: " << overflow << endl;
	cout << "\tCalculo do endereco de desvio (valor de resultado): " << novoPC << endl;
	cout << "\tValor do rc: " 		<< rc << endl;
}
