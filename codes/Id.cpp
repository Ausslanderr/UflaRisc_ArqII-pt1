#include "If.cpp"

class Id {
    private:
        Controle *sinaisControle;
        bitset<8> opcode;
        bitset<lengthRegister> ra; //bitset
	    bitset<lengthRegister> rb;
	    bitset<lengthRegister> rc;
        bitset<c16> const16; //16
	    bitset<c24> const24; //24
        Controle sinaisControle;
    public:
        Id(bitset<dataBus> instrucaoBinaria);
        ~Id();
        bitset<8> getOpcode()           {return opcode;};
        bitset<lengthRegister> getRa()  {return ra;};
        bitset<lengthRegister> getRb()  {return rb;};
        bitset<lengthRegister> getRc()  {return rc;};
        bitset<c16> getConst16()        {return const16;};
        bitset<c24> getConst24()        {return const24;};
        Controle* getControle()          {return sinaisControle;};
        //void alter_Sinais(string opcode);
        void reset_valores ();
        void enviarOpcode(string auxOpcode);
        // Metodo de depuração está no Controle.
};

Id::Id(bitset<dataBus> instrucaoBinaria) {

    reset_valores();
    decodificarInstrucao(instrucaoBinaria);
}

Id::~Id(){
}
void Id::reset_valores (){
    opcode = 0;
    const24 = 0;
    const16 = 0;
    ra = -1;
    rb = -1;
    rc = -1;
}
void Id::enviarOpcode(string auxOpcode){
    sinaisControle.alterarSinais(auxOpcode);
}
void Id::decodificarInstrucao (If *Aux){
    // reorganizar tudo aqui
    
    bitset<dataBus> instrucaoBinaria = Aux->getInstrucao(); //instrucao 32 bits
    string instrucaoString = instrucaoBinaria.to_string(); //instrucao 32 bits em string
    string texto_Binario_Auxiliar;

    string auxOpcode = instrucaoString.substr(0, 8); //opcode string pra ser comparado na classe Controle
    enviarOpcode(auxOpcode); // enviando os sinais de controle para a classe configura-los

    
    texto_Binario_Auxiliar = instrucaoString.substr(8, lengthRegister);//extrai os 8 bits do primeiro operando
	ra = bitset<lengthRegister> (texto_Binario_Auxiliar);
	
	texto_Binario_Auxiliar = instrucaoString.substr(16, lengthRegister);//extrai os 8 bits do segundo operando
	rb = bitset<lengthRegister> (texto_Binario_Auxiliar);
	
	texto_Binario_Auxiliar = instrucaoString.substr(24, lengthRegister);//extrai os 8 bits do terceiro operando
	rc = bitset<lengthRegister> (texto_Binario_Auxiliar);

    texto_Binario_Auxiliar = instrucaoString.substr(0, c24);
    bitset<c24> auxConst24 (texto_Binario_Auxiliar);
    const24 = auxConst24.to_ulong();

    texto_Binario_Auxiliar = instrucaoString.substr(7, c16);
    bitset<c16> auxConst16 (texto_Binario_Auxiliar);
    const16 = auxConst16.to_ulong();
}
