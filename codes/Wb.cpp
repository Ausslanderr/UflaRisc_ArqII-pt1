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

      //bitset<addressBus> novoRa(alu->getRetornoFuncao()); ??? seria o certo, porém setRegistrador só recebe bitset com dataBus(32bits)
		
		reg->setRegistrador(novoRa, 31);
	}
	
	// lw
	else if(controle->getRegwrite() == 1 and controle->getMemtoReg() == 1){

		bitset<dataBus> novoDado(alu->getResultado());

		reg->setRegistrador(novoDado, id->getRa());
	}
	
	else if(controle->getRegwrite() == 1 and controle->getRegdst() == 1 and alu->getOverflow() == 0){
				
		bitset<dataBus> novoDado(alu->getResultado());
		
		reg->setRegistrador(novoDado, id->getRb());
	}
	
	else if(controle->getRegwrite() == 1 and controle->getRegdst() == 0 and alu->getOverflow() == 0){
		
		bitset<dataBus> novoDado(alu->getResultado());
		
		reg->setRegistrador(novoDado, id->getRa());
	}
}


