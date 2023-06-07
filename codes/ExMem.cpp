
class ExMem{
	
	private:
	
		Alu *alu;
		Controle *controle;
		
	public:
		ExMem(Id *idStage, If *ifStage);
		void realizarOperacoes();
};

ExMem::ExMem(Id *idStage, If *ifStage) {

	//controle = idStage->sinaisControle; // Tem o mesmo problema aqui e no codigo do Davi. Os tipos são compativeis, mas de alguma forma ele nao permite igualar a posicao de memoria
	alu = new Alu(idStage, ifStage);

	cout << idStage->getControle()->getAluctrl() << endl;

}

void ExMem::realizarOperacoes(){
	
	// Realiza os calculos aritmeticos
	if((controle->getBranch() == 0) && (controle->getJump() == 0) && (controle->getMemwrite() == 0) && (controle->getMemread() == 0))
		alu->instrucoesAritmeticas();
		
	// Realiza os calculos dos desvios
	else if((controle->getBranch() == 1) || (controle->getJump() == 1))
		alu->instrucoesDeDesvio();
		
	// Realiza os calculos para armazenar valores na memoria
	else if((controle->getBranch() == 0) && (controle->getJump() == 0) && ((controle->getMemwrite() == 1) || (controle->getMemread() == 1)))
		alu->instrucoesDeMemoria();
}
