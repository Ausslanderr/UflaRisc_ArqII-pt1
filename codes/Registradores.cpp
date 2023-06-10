class Registradores {

    private:
		bitset<dataBus> *vetorReg;

    public:
        Registradores();
		~Registradores();
        bitset<dataBus> getRegistrador(bitset<lengthRegister> numeroRegistrador);
        void setRegistrador(bitset<dataBus> dadoParaEscrever, bitset<lengthRegister> numeroRegistrador);
};

Registradores::Registradores() {

	vetorReg = new bitset<dataBus>[numRegistradores];

	vetorReg[28] = limiteTamanhoMemoriaTexto;	// gp
	vetorReg[29] = tamanhoMemoria - 1;	// sp
}

Registradores::~Registradores() {

	cout << "registrador morreu" << endl;

	delete[] vetorReg;
}

bitset<dataBus> Registradores::getRegistrador(bitset<lengthRegister> numeroRegistrador){

	if(numeroRegistrador == bitset<lengthRegister> ("00000000")) {
		return vetorReg[0];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000001")) {
		return vetorReg[1];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000010")) {
		return vetorReg[2];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000011")) {
		return vetorReg[3];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000100")) {
		return vetorReg[4];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000101")) {
		return vetorReg[5];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000110")) {
		return vetorReg[6];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000111")) {
		return vetorReg[7];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001000")) {
		return vetorReg[8];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001001")) {
		return vetorReg[9];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001010")) {
		return vetorReg[10];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001011")) {
		return vetorReg[11];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001100")) {
		return vetorReg[12];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001101")) {
		return vetorReg[13];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001110")) {
		return vetorReg[14];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001111")) {
		return vetorReg[15];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010000")) {
		return vetorReg[16];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010001")) {
		return vetorReg[17];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010010")) {
		return vetorReg[18];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010011")) {
		return vetorReg[19];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010100")) {
		return vetorReg[20];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010101")) {
		return vetorReg[21];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010110")) {
		return vetorReg[22];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010111")) {
		return vetorReg[23];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011000")) {
		return vetorReg[24];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011001")) {
		return vetorReg[25];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011010")) {
		return vetorReg[26];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011011")) {
		return vetorReg[27];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011100")) {
		return vetorReg[28];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011101")) {
		return vetorReg[29];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011110")) {
		return vetorReg[30];
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011111")) {
		return vetorReg[31];
	}
	throw(6);
}

void Registradores::setRegistrador(bitset<dataBus> dadoParaEscrever, bitset<lengthRegister> numeroRegistrador){

	if(numeroRegistrador == bitset<lengthRegister> ("00000000")) {
		throw(7);
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000001")) {
		vetorReg[1] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000010")) {
		vetorReg[2] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000011")) {
		vetorReg[3] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000100")) {
		vetorReg[4] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000101")) {
		vetorReg[5] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000110")) {
		vetorReg[6] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00000111")) {
		vetorReg[7] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001000")) {
		vetorReg[8] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001001")) {
		vetorReg[9] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001010")) {
		vetorReg[10] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001011")) {
		vetorReg[11] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001100")) {
		vetorReg[12] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001101")) {
		vetorReg[13] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001110")) {
		vetorReg[14] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00001111")) {
		vetorReg[15] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010000")) {
		vetorReg[16] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010001")) {
		vetorReg[17] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010010")) {
		vetorReg[18] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010011")) {
		vetorReg[19] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010100")) {
		vetorReg[20] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010101")) {
		vetorReg[21] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010110")) {
		vetorReg[22] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00010111")) {
		vetorReg[23] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011000")) {
		vetorReg[24] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011001")) {
		vetorReg[25] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011010")) {
		throw(8);
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011011")) {
		throw(8);
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011100")) {
		vetorReg[28] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011101")) {
		vetorReg[29] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011110")) {
		vetorReg[30] = dadoParaEscrever;
	}
	else if(numeroRegistrador == bitset<lengthRegister> ("00011111")) {
		vetorReg[31] = dadoParaEscrever;
	}
	else {
		throw(9);
	}
}
