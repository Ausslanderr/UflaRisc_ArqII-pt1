class Alu {

    private:
        bitset<dataBus> resultado;
		Id *idStage;
		Controle *sinaisControle;
        bool ALUzero;
		bool zero;
		bool overflow;
		bool carry;
        bool borrow;
		bool neg;
        void verificaNegativo(bitset<8> rc);
		void verificaOverflow(bitset<8> ra, string operacao);
        bitset<8> calculaBits(bitset<8> ra, bitset<8> rb, string operacao);

    public:
        Alu(Id *idStage, Controle *sinaisControle);
        void instrucoesAritmeticas();
        void instrucoesDeDesvio();
        void instrucoesDeMemoria();
        void mostrarFlags();
		//void resetFlagsDesvio(); Isso vai ser necessario, mesmo possuindo o construtor?
        
};

Alu::Alu(Id *idStage, Controle *sinaisControle) {

	this->idStage = idStage;
	this->sinaisControle = sinaisControle;

    //address = ??
    //end = ??

    ALUzero = 0;
    zero = 0;
    overflow = 0;
	carry = 0;
    borrow = 0;
	neg = 0;
}

void Alu::instrucoesAritmeticas(){
	
	// SOMA INTEIRA
	if(sinaisControle->getAluctrl() == "add"){
		resultado = calculaBits(idStage->getRa(), idStage->getRb(), "adicao");
		verificaNegativo(resultado);
		zero = resultado;
		
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
	
	// SHIFT ARITMÉTICO PARA A ESQUERDA (vou refazer)
	if(sinaisControle->getAluctrl() == "asl"){
		//rc = ra << rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de asl" << endl << endl;
	}
	
	// SHIFT ARITMÉTICO PARA A DIREITA (vou refazer)
	if(sinaisControle->getAluctrl() == "asr"){
		//rc = ra >> rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de asr" << endl << endl;
	}

	// SHIFT LÓGICO PARA A ESQUERDA (vou refazer)
	if(sinaisControle->getAluctrl() == "lsl"){
		//rc = ra << rb;
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lsl" << endl << endl;
	}
	
	// SHIFT LÓGICO PARA A DIREITA (vou refazer)
	if(sinaisControle->getAluctrl() == "lsr"){
		//rc = ra >> rb;
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
		//rc = (Const16 << 16) | (rc & num);
		// nao causa overflow
		verificaNegativo(rc);
		zero = rc;
		
		cout << "Eh uma instrucao de lch" << endl << endl;
	}
	
	// CARREGA CONSTANTE NOS 2 BYTES MENOS SIGNIFICATIVOS
	if(sinaisControle->getAluctrl() == "lcl"){
		//rc = Const16 | (rc & num);
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
	
    
	if(PC != 0){
		//preciso alterar o PC se ele foi modificado
	}
    
}

void Alu::instrucoesDeMemoria(){
	
	// LOAD WORD (vou refazer)
	if(sinaisControle->getAluctrl() == "load"){
		//rc = memória[ra];
		cout << "Eh uma instrucao de load" << endl << endl;
	}
	
	// STORE WORD (vou refazer)
	if(sinaisControle->getAluctrl() == "store"){
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
	cout << "\tCalculo do endereco de desvio (valor de resultado): " << resultado << endl;
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
