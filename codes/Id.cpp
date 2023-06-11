#include "Controle.cpp"

class Id {

    private:
        Controle *sinaisControle;
        Registradores *regs;
        bitset<c8> opcode;
        bitset<lengthRegister> ra;
        bitset<dataBus> raValue;
	    bitset<lengthRegister> rb;
        bitset<dataBus> rbValue;
	    bitset<lengthRegister> rc;
        bitset<dataBus> rcValue;
        bitset<c8> const8;
        bitset<c16> const16;
	    bitset<c24> const24;
        void reset_valores();
        void decodificarInstrucao(bitset<dataBus> instrucaoBinaria);
        bool verificarRegistrador(string textoBin);

    public:
        Id(bitset<dataBus> instrucaoBinaria, Registradores *regs);
        ~Id();
        bitset<8> getOpcode()           {return opcode;};
        bitset<lengthRegister> getRa()  {return ra;};
        bitset<dataBus> getRaValue()    {return raValue;};
        bitset<lengthRegister> getRb()  {return rb;};
        bitset<dataBus> getRbValue()    {return rbValue;};
        bitset<lengthRegister> getRc()  {return rc;};
        bitset<dataBus> getRcValue()    {return rcValue;};
        bitset<c16> getConst16()        {return const16;};
        bitset<c24> getConst24()        {return const24;};
        bitset<c8> getConst8()          {return const8;};
        Controle* getControle()         {return sinaisControle;};
        void depuracao();
};

Id::Id(bitset<dataBus> instrucaoBinaria, Registradores *regs) {

    reset_valores();
    this->regs = regs;
    decodificarInstrucao(instrucaoBinaria);
}

Id::~Id(){

    delete sinaisControle;

    cout << "Id morreu" << endl;
}

void Id::reset_valores() {

    opcode.reset();
    ra = -1;
    raValue.reset();
	rb = -1;
    rbValue.reset();
	rc = -1;
    rcValue.reset();
    const8.reset();
    const16.reset();
	const24.reset();
}

void Id::decodificarInstrucao(bitset<dataBus> instrucaoBinaria) {
    
    string instrucaoString = instrucaoBinaria.to_string();  // instrucao 32 bits em string
    string texto_Binario_Auxiliar;

    string auxOpcode = instrucaoString.substr(0, c8);    // opcode string pra ser comparado na classe Controle
    opcode = bitset<c8> (auxOpcode);
    sinaisControle = new Controle(auxOpcode);   // enviando o opcode para a classe controle, para configurar os sinais das flags
    
    texto_Binario_Auxiliar = instrucaoString.substr(c8, lengthRegister);    // extrai os 8 bits do primeiro operando (ra)
    if(verificarRegistrador(texto_Binario_Auxiliar)) {
        ra = bitset<lengthRegister> (texto_Binario_Auxiliar);
        raValue = regs->getRegistrador(ra);
    }
	
	texto_Binario_Auxiliar = instrucaoString.substr(c16, lengthRegister);   // extrai os 8 bits do segundo operando (rb)
    if(verificarRegistrador(texto_Binario_Auxiliar)) {
        rb = bitset<lengthRegister> (texto_Binario_Auxiliar);
        rbValue = regs->getRegistrador(rb);
    }
	
	texto_Binario_Auxiliar = instrucaoString.substr(c24, lengthRegister);   // extrai os 8 bits do terceiro operando (rc)
    if(verificarRegistrador(texto_Binario_Auxiliar)) {
        rc = bitset<lengthRegister> (texto_Binario_Auxiliar);
        rcValue = regs->getRegistrador(rc);
    }

    // extrai os bits de cada constante
    texto_Binario_Auxiliar = instrucaoString.substr(c24, c8);
    const8 = bitset<c8> (texto_Binario_Auxiliar);

    texto_Binario_Auxiliar = instrucaoString.substr(c8, c16);
    const16 = bitset<c16> (texto_Binario_Auxiliar);

    texto_Binario_Auxiliar = instrucaoString.substr(c8, c24);
    const24 = bitset<c24> (texto_Binario_Auxiliar);
}

bool Id::verificarRegistrador(string textoBin) {

    int resultado = 0;
	int potencia_dois = 1;
	
	for(int i = textoBin.size() - 1; i >= 0; i--) {
		
		if(textoBin[i] == '1') {
            resultado += potencia_dois;
        }
		potencia_dois *= 2;
	}

    if(resultado >= 0 and resultado <= 31) {
        return true;
    }

    return false;
}

void Id::depuracao() {

    cout << "Valores das variáveis do Id: " << endl;
    cout << "\tOpcode: "                << opcode << endl;
    cout << "\tRa (endereço): "         << ra.to_ulong() << endl;
    cout << "\tRb (endereço): "         << rb.to_ulong() << endl;
    cout << "\tRc (endereço): "         << rc.to_ulong() << endl;
    cout << "\tconst8 : "               << const8 << endl;
    cout << "\tconst16: "               << const16 << endl;
    cout << "\tconst24: "               << const24 << endl << endl;

    sinaisControle->depuracao_controle();
}
