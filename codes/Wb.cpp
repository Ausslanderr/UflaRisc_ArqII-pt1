class Wb{
	
	private:
		Registradores *reg;
		Controle *controle;
		ExMem *estagioExMem;
        Alu *alu;
		Id *id;

		
	public:
		Wb(Registradores *regPointer, Controle *controlePointer, ExMem *estagioExMemPointer, Alu *aluPointer, Id *idPointer);
		void leituraEscritaRegistrador();
};

Wb::Wb(Registradores *regPointer, Controle *controlePointer, ExMem *estagioExMemPointer, Alu *aluPointer, Id *idPointer){
	
	reg = regPointer;
	controle = controlePointer;
	estagioExMem = estagioExMemPointer;
    alu = aluPointer;
	id = idPointer;
	
}

void Wb::leituraEscritaRegistrador(){
	
	// jal
	if(controle->getRegwrite() == 1 and controle->getJump() == 1){

      bitset<dataBus> novoR31(alu->getRetornoFuncao()); 
		
		reg->setRegistrador(novoR31, 31);
	}
	
	// lw
	else if(controle->getRegwrite() == 1 and controle->getMemtoReg() == 1){

		bitset<dataBus> novoDado(alu->getResultadoRc());

		reg->setRegistrador(novoDado, id->getRa());
	}

	// sw
	else if(controle->getRegwrite() == 0  and controle->getMemwrite() == 1){

		bitset<dataBus> novoDado(alu->getResultadoRa());

		reg->setRegistrador(novoDado, id->getRc());
	}
	
	// R
	else if(controle->getRegwrite() == 1 and controle->getRegdst() == 1 and alu->getOverflow() == 0){
				
		bitset<dataBus> novoDado(alu->getResultadoRc());
		
		reg->setRegistrador(novoDado, id->getRc());
	}
	
	else if(controle->getRegwrite() == 1 and controle->getRegdst() == 0 and alu->getOverflow() == 0){
		
		bitset<dataBus> novoDado(alu->getResultadoRc());
		
		reg->setRegistrador(novoDado, id->getRa());
	}
}


