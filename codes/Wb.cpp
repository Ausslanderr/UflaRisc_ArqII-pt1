class Wb{
	
	private:
		Registradores *regs;
		Id *idStage;
		Controle *controle;
        Alu *alu;
		Memoria *memoria;
		void leituraEscritaRegistrador();
		
	public:
		Wb(Registradores *regs, Id *idStage, Controle *controle, Alu *alu, Memoria *memoria);
		~Wb();
};

Wb::Wb(Registradores *regs, Id *idStage, Controle *controle, Alu *alu, Memoria *memoria){
	
	this->regs = regs;
	this->idStage = idStage;
	this->controle = controle;
	this->alu = alu;
	this->memoria = memoria;

	leituraEscritaRegistrador();
}

Wb::~Wb() {

	cout << "wb morreu" << endl;
}

void Wb::leituraEscritaRegistrador(){
	
	// jal
	if(controle->getRegwrite() == 1 and controle->getJump() == 1){

      bitset<dataBus> novoR31(alu->getRetornoFuncao()); 
		
		regs->setRegistrador(novoR31, 31);
	}
	
	// lw
	else if(controle->getRegwrite() == 1 and controle->getMemtoReg() == 1){

		bitset<dataBus> novoDado = memoria->getDado(alu->getResultadoRa());

		regs->setRegistrador(novoDado, idStage->getRc());
	}
	
	// addi e subi
	else if(controle->getRegwrite() == 1 and controle->getRegdst() == 1 and alu->getOverflow() == 0){
				
		bitset<dataBus> novoDado(alu->getResultadoRc());
		
		regs->setRegistrador(novoDado, idStage->getRa());
	}

	// R
	else if(controle->getRegwrite() == 1 and controle->getRegdst() == 0 and alu->getOverflow() == 0){
				
		bitset<dataBus> novoDado(alu->getResultadoRc());
		
		regs->setRegistrador(novoDado, idStage->getRc());
	}
}
