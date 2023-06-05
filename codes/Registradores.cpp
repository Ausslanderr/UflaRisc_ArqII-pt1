class Registradores {

    private:
		bitset<dataBus> *vetorReg;

    public:
        Registradores();
		~Registradores();
        bitset<dataBus> getRegistrador(int numeroRegistrador);
        void setRegistrador(bitset<dataBus> dadoParaEscrever, int numeroRegistrador);
};

Registradores::Registradores() {

	vetorReg = new bitset<dataBus>[numRegistradores];
}

Registradores::~Registradores() {

	cout << "registrador morreu" << endl;

	delete[] vetorReg;
}

bitset<dataBus> Registradores::getRegistrador(int numeroRegistrador){
	
	if(numeroRegistrador >= 0 and numeroRegistrador <= 31) {

		return vetorReg[numeroRegistrador];
	}

	throw(6);
}

void Registradores::setRegistrador(bitset<dataBus> dadoParaEscrever, int numeroRegistrador){
	
	switch(numeroRegistrador){
		
		case 0:
			throw(7);
			break;
			
		case 1:
			vetorReg[1] = dadoParaEscrever;
			break;
			
		case 2:
			vetorReg[2] = dadoParaEscrever;
			break;
			
		case 3:
			vetorReg[3] = dadoParaEscrever;
			break;
			
		case 4:
			vetorReg[4] = dadoParaEscrever;
			break;
			
		case 5:
			vetorReg[5] = dadoParaEscrever;
			break;
			
		case 6:
			vetorReg[6] = dadoParaEscrever;
			break;
			
		case 7:
			vetorReg[7] = dadoParaEscrever;
			break;
			
		case 8:
			vetorReg[8] = dadoParaEscrever;
			break;
			
		case 9:
			vetorReg[9] = dadoParaEscrever;
			break;
			
		case 10:
			vetorReg[10] = dadoParaEscrever;
			break;
			
		case 11:
			vetorReg[11] = dadoParaEscrever;
			break;
			
		case 12:
			vetorReg[12] = dadoParaEscrever;
			break;
			
		case 13:
			vetorReg[13] = dadoParaEscrever;
			break;
			
		case 14:
			vetorReg[14] = dadoParaEscrever;
			break;
			
		case 15:
			vetorReg[15] = dadoParaEscrever;
			break;
			
		case 16:
			vetorReg[16] = dadoParaEscrever;
			break;
			
		case 17:
			vetorReg[17] = dadoParaEscrever;
			break;
			
		case 18:
			vetorReg[18] = dadoParaEscrever;
			break;
			
		case 19:
			vetorReg[19] = dadoParaEscrever;
			break;
			
		case 20:
			vetorReg[20] = dadoParaEscrever;
			break;
			
		case 21:
			vetorReg[21] = dadoParaEscrever;
			break;
			
		case 22:
			vetorReg[22] = dadoParaEscrever;
			break;
			
		case 23:
			vetorReg[23] = dadoParaEscrever;
			break;
			
		case 24:
			vetorReg[24] = dadoParaEscrever;
			break;
			
		case 25:
			vetorReg[25] = dadoParaEscrever;
			break;
			
		case 26:
			throw(8);
			break;
			
		case 27:
			throw(8);
			break;
			
		case 28:
			vetorReg[28] = dadoParaEscrever;
			break;
			
		case 29:
			vetorReg[29] = dadoParaEscrever;
			break;
			
		case 30:
			vetorReg[30] = dadoParaEscrever;
			break;
			
		case 31:
			vetorReg[31] = dadoParaEscrever;
			break;
	}
}
