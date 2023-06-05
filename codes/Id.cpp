#include "If.cpp"

class Id {
    private:
        bitset<8> opcode;
        bitset<lengthRegister> ra; //bitset
	    bitset<lengthRegister> rb;
	    bitset<lengthRegister> rc;
        bitset<c16> const16; //16
	    bitset<c24> const24; //24
        Controle sinaisControle;
    public:
        Id();
        ~Id();
        void decodificarInstrucao (If *Aux);
        //void alter_Sinais(string opcode);
        void reset_valores ();
        void enviarOpcode(string auxOpcode);
        // Metodo de depuração está no Controle.
};

Id::Id() {
    
        sinaisControle.valuesReset();
        bitset<8> opcode = 0;
        bitset<lengthRegister> ra = 0; //bitset
	    bitset<lengthRegister> rb = 0;
	    bitset<lengthRegister> rc = 0;
        bitset<c16> const16 = 0; //16
	    bitset<c24> const24 = 0; //24
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

    
    texto_Binario_Auxiliar = instrucaoString.substr(7, lengthRegister);//extrai os 8 bits do primeiro operando
	bitset<8> aux_rs (texto_Binario_Auxiliar);
	ra = aux_rs.to_ulong();
	
	texto_Binario_Auxiliar = instrucaoString.substr(15, lengthRegister);//extrai os 8 bits do segundo operando
	bitset<8> aux_rt (texto_Binario_Auxiliar);
	rb = aux_rt.to_ulong();
	
	texto_Binario_Auxiliar = instrucaoString.substr(23, lengthRegister);//extrai os 8 bits do terceiro operando
	bitset<8> aux_rd (texto_Binario_Auxiliar);
	rc = aux_rd.to_ulong();

    texto_Binario_Auxiliar = instrucaoString.substr(0, c24);
    bitset<c24> auxConst24 (texto_Binario_Auxiliar);
    const24 = auxConst24.to_ulong();

    texto_Binario_Auxiliar = instrucaoString.substr(7, c16);
    bitset<c16> auxConst16 (texto_Binario_Auxiliar);
    const16 = auxConst16.to_ulong();
}
