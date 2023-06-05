class Registradores {

    private:
		bitset<dataBus> vetorReg[numRegistradores];

	/*
        bitset<tamanhoInstrucao> zero;	// valor constante de zero
		bitset<tamanhoInstrucao> at;	// reservado pelo compilador
		bitset<tamanhoInstrucao> v0, v1;	// variaveis para retorno de funcoes e outras utilidades
		bitset<tamanhoInstrucao> a0, a1, a2, a3;	// argumentos
		bitset<tamanhoInstrucao> t0, t1, t2, t3, t4, t5, t6, t7;	// variaveis temporarias
		bitset<tamanhoInstrucao> s0, s1, s2, s3, s4, s5, s6, s7;	// variaveis salvas
		bitset<tamanhoInstrucao> t8, t9;	// variaveis usadas na adicao dos temporarios
		bitset<tamanhoInstrucao> k0, k1;	// reservado pelo OS
		bitset<tamanhoInstrucao> gp;	// global pointer
		bitset<tamanhoInstrucao> sp;	// stack pointer
		bitset<tamanhoInstrucao> fp;	// frame pointer
		bitset<tamanhoInstrucao> ra;	// retorno de função
		*/

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

	delete[] vetorReg;
}

bitset<dataBus> Registradores::retornarRegistrador(int numeroRegistrador){
	
	return vetorReg[numeroRegistrador];
	
	/*
	if(numeroRegistrador == 0) return vetorReg[0]; //zero
	if(numeroRegistrador == 1) return vetorReg[1]; //at
	if(numeroRegistrador == 2) return vetorReg[2]; //v0
	if(numeroRegistrador == 3) return vetorReg[3]; //v1
	if(numeroRegistrador == 4) return vetorReg[4]; //a0
	if(numeroRegistrador == 5) return vetorReg[5]; //a1;
	if(numeroRegistrador == 6) return vetorReg[6]; //a2;
	if(numeroRegistrador == 7) return vetorReg[7]; //a3;
	if(numeroRegistrador == 8) return vetorReg[8]; //t0;
	if(numeroRegistrador == 9) return vetorReg[9]; //t1;
	if(numeroRegistrador == 10) return vetorReg[10]; //t2;
	if(numeroRegistrador == 11) return vetorReg[11]; //t3;
	if(numeroRegistrador == 12) return vetorReg[12]; //t4;
	if(numeroRegistrador == 13) return vetorReg[13]; //t5;		//Guarda depois
	if(numeroRegistrador == 14) return vetorReg[14]; //t6;
	if(numeroRegistrador == 15) return vetorReg[15]; //t7;
	if(numeroRegistrador == 16) return vetorReg[16]; //s0;
	if(numeroRegistrador == 17) return vetorReg[17]; //s1;
	if(numeroRegistrador == 18) return vetorReg[18]; //s2;
	if(numeroRegistrador == 19) return vetorReg[19]; //s3;
	if(numeroRegistrador == 20) return vetorReg[20]; //s4;
	if(numeroRegistrador == 21) return vetorReg[21]; //s5;
	if(numeroRegistrador == 22) return vetorReg[22]; //s6;
	if(numeroRegistrador == 23) return vetorReg[23]; //s7;
	if(numeroRegistrador == 24) return vetorReg[24]; //t8;
	if(numeroRegistrador == 25) return vetorReg[25]; //t9;
	if(numeroRegistrador == 26) return vetorReg[26]; //k0;
	if(numeroRegistrador == 27) return vetorReg[27]; //k1;
	if(numeroRegistrador == 28) return vetorReg[28]; //gp;
	if(numeroRegistrador == 29) return vetorReg[29]; //sp;
	if(numeroRegistrador == 30) return vetorReg[30]; //fp;
	if(numeroRegistrador == 31) return vetorReg[31]; //ra;
	*/
	
	throw runtime_error("ERRO LEITURA DO REGISTRADOR - o registrador lido nao pertence ao conjunto de registradores existentes!");
}

void Registradores::setRegistrador(bitset<dataBus> dadoParaEscrever, int numeroRegistrador){
	
	switch(numeroRegistrador){
		
		case 0:
			throw runtime_error("Tentativa de setar algum valor no registrador zero - NEGADO!");
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
			throw(7);
			break;
			
		case 27:
			throw(7);
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
