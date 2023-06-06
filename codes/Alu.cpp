class Alu {

    private:

        bitset<32> PC, r31, adress, end; // talvez seja necessario mudar o tamanho do bitset em alguma dessas variaveis
		bitset<8> ra, rb, rc, num, zero;
		bitset<16> Const16;
		Controle *controle;
		If *ifStage;
        bool ALUzero;
		bool overflow;
		bool carry;
        bool borrow;
		bool neg;

        void verificaNegativo(bitset<8> rc);
		void verificaOverflow(bitset<8> ra, string operacao);
        bitset<8> calculaBits(bitset<8> ra, bitset<8> rb, string operacao);

    public:
        Alu(Id *idStage, If *ifStage);
        void instrucoesAritmeticas();
        void instrucoesDeDesvio();
        void instrucoesDeMemoria();
        void mostrarFlags();
		//void resetFlagsDesvio(); Isso vai ser necessario, mesmo possuindo o construtor?
        
};

Alu::Alu(Id *idStage, If *ifStage) {

	//controle = idStage->sinaisControle; // Tem o mesmo problema aqui e no codigo do Davi. Os tipos são compativeis, mas de alguma forma ele nao permite igualar a posicao de memoria
	this->ifStage = ifStage;

	cout << idStage->getControle()->getAluctrl() << endl;

    PC = ifStage->getInstrucao();
    Const16 = idStage->getConst16(); 
    ra = idStage->getRa();
	rb = idStage->getRb();
    rc = idStage->getRc();
    //r31 = ??
    //adress = ??
    //end = ??

	num = 1111111111111111; // 65535 em binario
    ALUzero = 0;
    zero = 0;
    overflow = 0;
	carry = 0;
    borrow = 0;
	neg = 0;
    
}

void Alu::instrucoesAritmeticas(){
	
	// SOMA INTEIRA
	if(controle->getAluctrl() == "add"){
		rc = calculaBits(ra, rb, "adicao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de add" << endl << endl;
	}
	
	// SUBTRAÇÃO INTEIRA
	if(controle->getAluctrl() == "sub"){
		rc = calculaBits(ra, rb, "subtracao");
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de sub" << endl << endl;
	}
	
	// ZERA
	if(controle->getAluctrl() == "zeros"){
		rc = 0;
		// nao causa overflow
		// neg por padrao é zero
		zero = rc;
		
		cout << "Eh uma instrucao de zeros" << endl << endl;
	}
	
	// XOR LÓGICO
	if(controle->getAluctrl() == "xor"){
		rc = ra ^ rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;

		cout << "Eh uma instrucao de xor" << endl << endl;
	}
	
	// OR LÓGICO
	if(controle->getAluctrl() == "or"){
		rc = ra | rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de or" << endl << endl;
	}
	
	// NOT
	if(controle->getAluctrl() == "passnota"){
		rc = ~ra;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de passnota" << endl << endl;
	}
	
	// AND LÓGICO
	if(controle->getAluctrl() == "and"){
		rc = ra & rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de and" << endl << endl;
	}
	
	// SHIFT ARITMÉTICO PARA A ESQUERDA (vou refazer)
	if(controle->getAluctrl() == "asl"){
		//rc = ra << rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de asl" << endl << endl;
	}
	
	// SHIFT ARITMÉTICO PARA A DIREITA (vou refazer)
	if(controle->getAluctrl() == "asr"){
		//rc = ra >> rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de asr" << endl << endl;
	}

	// SHIFT LÓGICO PARA A ESQUERDA (vou refazer)
	if(controle->getAluctrl() == "lsl"){
		//rc = ra << rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lsl" << endl << endl;
	}
	
	// SHIFT LÓGICO PARA A DIREITA (vou refazer)
	if(controle->getAluctrl() == "lsr"){
		//rc = ra >> rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lsr" << endl << endl;
	}
	
	// COPIA
	if(controle->getAluctrl() == "passa"){
		rc = ra;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de passa" << endl << endl;
	}
	
	// CARREGA CONSTANTE NOS 2 BYTES MAIS SIGNIFICATIVOS
	if(controle->getAluctrl() == "lch"){
		rc = (Const16 << 16) | (rc & num);
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lch" << endl << endl;
	}
	
	// CARREGA CONSTANTE NOS 2 BYTES MENOS SIGNIFICATIVOS
	if(controle->getAluctrl() == "lcl"){
		rc = Const16 | (rc & num);
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lcl" << endl << endl;
	}
	
	// Verifica se algum resultado corresponde a 0 para acionar a flag
	if(zero == 0){
		ALUzero = 1;
	}
}

void Alu::instrucoesDeDesvio(){

	// JUMP AND LINK
	if(controle->getAluctrl() == "jal"){
		r31 = PC; 
		PC = end;	
		cout << "Eh uma instrucao de jal" << endl << endl;
	}
	
	// JUMP REGISTER
	if(controle->getAluctrl() == "jr"){
		PC = r31;	
		cout << "Eh uma instrucao de jr" << endl << endl;
	}
	
	//  JUMP SE IGUAL (BEQ)
	if(controle->getAluctrl() == "beq"){
		PC = end; //tenho que tratar se j foi tomado (fazer um if)
		cout << "Eh uma instrucao de beq" << endl << endl;
	}
	
	//  JUMP SE DIFERENTE (BNE)
	if(controle->getAluctrl() == "bne"){
		PC = end; //tenho que tratar se j foi tomado (fazer um if)
		cout << "Eh uma instrucao de bne" << endl << endl;
	}
	
	//  JUMP INCONDICIONAL
	if(controle->getAluctrl() == "j"){
		PC = adress;
		cout << "Eh uma instrucao de j" << endl << endl;
	}
	
    
	if(PC != 0){
		//preciso alterar o PC se ele foi modificado
	}
    
}

void Alu::instrucoesDeMemoria(){
	
	// LOAD WORD (vou refazer)
	if(controle->getAluctrl() == "load"){
		//rc = memória[ra];
		cout << "Eh uma instrucao de load" << endl << endl;
	}
	
	// STORE WORD (vou refazer)
	if(controle->getAluctrl() == "store"){
		//memória[rc] = ra;
		cout << "Eh uma instrucao de store" << endl << endl;
	}
}

bitset<8> Alu::calculaBits(bitset<8> ra, bitset<8> rb, string operacao){
	
	// adicao
	if((operacao == "adicao")){
		
        bitset<8> sum;
	
		for (int i = 0; i < 8; i++) {
			sum[i] = ra[i] ^ rb[i] ^ carry;  // Soma bit a bit com carry
			carry = (ra[i] & rb[i]) | (carry & (ra[i] ^ rb[i]));  // Calcula o carry para o próximo bit
		}

		verificaOverflow(ra, operacao);
        return sum;
    }
		
	// subtracao
	if((operacao == "subtracao")){
		bitset<8> difference;
		
		for (int i = 0; i < 8; i++) {
			difference[i] = ra[i] ^ rb[i] ^ borrow;  // Subtrai bit a bit com borrow
			borrow = (!ra[i] & rb[i]) | (borrow & (ra[i] ^ rb[i]));  // Calcula o borrow para o próximo bit
		}

		verificaOverflow(ra, operacao);
        return difference;
    }

    return 0;
			
}

void Alu::verificaOverflow(bitset<8> ra, string operacao){

	if(operacao == "adicao"){
		overflow = carry;
	}
	
	if(operacao == "subtracao"){
		overflow = (borrow != ra[7]);
	}

}

void Alu::verificaNegativo(bitset<8> rc){

	// Verifica se o bit mais significativo é 1 (Se é negativo)
	if (rc[7]) {
        neg = 1;
    }

}

void Alu::mostrarFlags(){
	
	cout << "Flags da ALU e endereco de desvio: " << endl;
	cout << "\tFlag de Zero: " << ALUzero << endl;
    cout << "\tCarry: " << carry << endl;
    cout << "\tNegativo: " << neg << endl;
	cout << "\tSinal de Overflow: " << overflow << endl;
	cout << "\tCalculo do endereco de desvio: " << PC << endl;
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
