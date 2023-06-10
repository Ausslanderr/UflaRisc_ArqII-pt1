class Wb{
	
	private:
		Registradores *regs;
		Id *idStage;
		Controle *controle;
        Alu *alu;
		void leituraEscritaRegistrador();
		
	public:
		Wb(Registradores *regs, Id *idStage, Controle *controle, Alu *alu);
		~Wb();
};

Wb::Wb(Registradores *regs, Id *idStage, Controle *controle, Alu *alu){
	
	this->regs = regs;
	this->idStage = idStage;
	this->controle = controle;
	this->alu = alu;

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

		bitset<dataBus> novoDado(alu->getResultadoRc());

		regs->setRegistrador(novoDado, idStage->getRa());
	}

	// sw
	else if(controle->getRegwrite() == 0  and controle->getMemwrite() == 1){

		bitset<dataBus> novoDado(alu->getResultadoRa());

		regs->setRegistrador(novoDado, idStage->getRc());
	}
	
	// R
	else if(controle->getRegwrite() == 1 and controle->getRegdst() == 1 and alu->getOverflow() == 0){
				
		bitset<dataBus> novoDado(alu->getResultadoRc());
		
		regs->setRegistrador(novoDado, idStage->getRc());
	}
	
	else if(controle->getRegwrite() == 1 and controle->getRegdst() == 0 and alu->getOverflow() == 0){
		
		bitset<dataBus> novoDado(alu->getResultadoRc());
		
		regs->setRegistrador(novoDado, idStage->getRa());
	}
}
