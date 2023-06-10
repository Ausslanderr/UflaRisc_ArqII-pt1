#include "Controle.cpp"

class Id {

    private:
        Controle *sinaisControle;
        Registradores *regs;
        bitset<8> opcode;
        bitset<lengthRegister> ra; //bitset
        bitset<dataBus> raValue;
	    bitset<lengthRegister> rb;
        bitset<dataBus> rbValue;
	    bitset<lengthRegister> rc;
        bitset<dataBus> rcValue;
        bitset<c8> const8; // 8
        bitset<c16> const16; //16
	    bitset<c24> const24; //24
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
        bitset<c8> getConst8()        {return const8;};
        Controle* getControle()         {return sinaisControle;};
        //void alter_Sinais(string opcode);
        // Metodo de depuração está no Controle.
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
    ra = -1; //bitset
    raValue.reset();
	rb = -1;
    rbValue.reset();
	rc = -1;
    rcValue.reset();
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
    if(verificarRegistrador(texto_Binario_Auxiliar)) {
        ra = bitset<lengthRegister> (texto_Binario_Auxiliar);
        raValue = regs->getRegistrador(ra);
    }
	
	texto_Binario_Auxiliar = instrucaoString.substr(16, lengthRegister);//extrai os 8 bits do segundo operando
    if(verificarRegistrador(texto_Binario_Auxiliar)) {
        rb = bitset<lengthRegister> (texto_Binario_Auxiliar);
        rbValue = regs->getRegistrador(rb);
    }
	
	texto_Binario_Auxiliar = instrucaoString.substr(24, lengthRegister);//extrai os 8 bits do terceiro operando
    if(verificarRegistrador(texto_Binario_Auxiliar)) {
        rc = bitset<lengthRegister> (texto_Binario_Auxiliar);
        rcValue = regs->getRegistrador(rc);
    }

    texto_Binario_Auxiliar = instrucaoString.substr(c24, 8);
    const8 = bitset<c8> (texto_Binario_Auxiliar);

    texto_Binario_Auxiliar = instrucaoString.substr(8, c16);
    const16 = bitset<c16> (texto_Binario_Auxiliar);

    texto_Binario_Auxiliar = instrucaoString.substr(8, c24);
    const24 = bitset<c24> (texto_Binario_Auxiliar);
}

bool Id::verificarRegistrador(string textoBin) {

    long resultado = 0;
	long potencia_dois = 1;
	
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
    cout << "\tOpcode: "    << opcode << endl;
    cout << "\tRa: "        << ra.to_ulong() << endl;
    cout << "\tRb: "        << rb.to_ulong() << endl;
    cout << "\tRc: "        << rc.to_ulong() << endl;
    cout << "\tconst16: "   << const16 << endl;
    cout << "\tconst24: "   << const24 << endl << endl;

    sinaisControle->depuracao_controle();
}
