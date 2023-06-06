#include "Controle.cpp"

class Id {

    private:
        bitset<8> opcode;
        bitset<lengthRegister> ra; //bitset
	    bitset<lengthRegister> rb;
	    bitset<lengthRegister> rc;
        bitset<c16> const16; //16
	    bitset<c24> const24; //24
        void reset_valores();
        void decodificarInstrucao(bitset<dataBus> instrucaoBinaria);

    public:
        Id(bitset<dataBus> instrucaoBinaria);
        ~Id();
        Controle *sinaisControle;
        bitset<8> getOpcode()           {return opcode;};
        bitset<lengthRegister> getRa()  {return ra;};
        bitset<lengthRegister> getRb()  {return rb;};
        bitset<lengthRegister> getRc()  {return rc;};
        bitset<c16> getConst16()        {return const16;};
        bitset<c24> getConst24()        {return const24;};
        //void alter_Sinais(string opcode);
        // Metodo de depuração está no Controle.
        void depuracao();
};

Id::Id(bitset<dataBus> instrucaoBinaria) {

    reset_valores();
    decodificarInstrucao(instrucaoBinaria);
}

Id::~Id(){

    cout << "Id morreu" << endl;

    delete sinaisControle;
}

void Id::reset_valores() {

    opcode.reset();
    ra = -1; //bitset
	rb = -1;
	rc = -1;
    const16.reset(); //16
	const24.reset(); //24
}

void Id::decodificarInstrucao(bitset<dataBus> instrucaoBinaria) {
    // reorganizar tudo aqui
    
    string instrucaoString = instrucaoBinaria.to_string(); //instrucao 32 bits em string
    string texto_Binario_Auxiliar;

    string auxOpcode = instrucaoString.substr(0, 8); //opcode string pra ser comparado na classe Controle
    opcode = bitset<8> (auxOpcode);
    sinaisControle = new Controle(auxOpcode); // enviando os sinais de controle para a classe configura-los
    
    texto_Binario_Auxiliar = instrucaoString.substr(8, lengthRegister);//extrai os 8 bits do primeiro operando
	ra = bitset<lengthRegister> (texto_Binario_Auxiliar);
	
	texto_Binario_Auxiliar = instrucaoString.substr(16, lengthRegister);//extrai os 8 bits do segundo operando
	rb = bitset<lengthRegister> (texto_Binario_Auxiliar);
	
	texto_Binario_Auxiliar = instrucaoString.substr(24, lengthRegister);//extrai os 8 bits do terceiro operando
	rc = bitset<lengthRegister> (texto_Binario_Auxiliar);

    texto_Binario_Auxiliar = instrucaoString.substr(8, c16);
    const16 = bitset<c16> (texto_Binario_Auxiliar);

    texto_Binario_Auxiliar = instrucaoString.substr(8, c24);
    const24 = bitset<c24> (texto_Binario_Auxiliar);
}

void Id::depuracao() {

    cout << "Valores das variáveis do Id: " << endl;
    cout << "\tOpcode: "    << opcode << endl;
    cout << "\tRa: "        << ra << endl;
    cout << "\tRb: "        << rb << endl;
    cout << "\tRc: "        << rc << endl;
    cout << "\tconst16: "   << const16 << endl;
    cout << "\tconst24: "   << const24 << endl << endl;

    sinaisControle->depuracao_controle();
}
