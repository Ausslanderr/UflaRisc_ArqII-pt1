class Controle {
    private:
        bool Regdst;
		bool Regwrite;
		string Aluctrl;
		bool Memread;
		bool Memwrite;
		int Aluop;
		bool Alusrc;
		bool MemtoReg;
		bool Branch;
		bool Jump;
    public :
        bool getRegdst (){return getRegdst;};
        bool getRegwrite(){return getRegwrite};
        string getAluctrl(){return getAluctrl};
        bool getMemread(){return getMemread};
        bool getMemwrite(){return getMemwrite};
        int getAluop(){return getAluctrl};
        bool getAlusrc(){return getAlusrc};
        bool getMemtoReg(){return  getMemtoReg};
        bool getBranch(){return getBranch};
        bool getJump(){return getJump};
        
        //Precisarei dos Set's ?...
        void valuesReset();
        void alterarSinais(string opcode);
        
}
Controle::Controle () {
    Regdst = 0;
    Regwrite = 0;
    Aluctrl = "invalido";
    Memread = 0;
    Memwrite = 0;
    Aluop = 0;
    Alusrc = 0;
    MemtoReg = 0;
    Branch = 0;
    Jump = 0;
}
Controle::~Controle () {

}
void Controle:: valuesReset(){
    Regdst = 0;
    Regwrite = 0;
    Aluctrl = "invalido";
    Memread = 0;
    Memwrite = 0;
    Aluop = 0;
    Alusrc = 0;
    MemtoReg = 0;
    Branch = 0;
    Jump = 0;
};
void Controle :: alterarSinais(string opcode){

    //Instruções do UFLA-RISC (23)

    if (opcode =="00000000"){ // address b.0
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "address";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00000001")// add b.1
    {
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "add";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00000010")// sub b.2
    {
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "sub";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 1;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00000011")// zero b.3
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "invalido";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00000100")// xor b.4
    {
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "xor";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00000101")// or b.5
    {
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "or";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00000110")// not b.6
    {
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "not";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00000111")// and b.7
    {
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "and";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00001000")// shift aritmético p/ esquerda b.8
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "shift aritmetic left";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00001001")// shift aritmético p/ direita b.9
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "shift aritmetic right";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    //verificar
    else if (opcode == "00001010")// shift lógico p/ esquerda b.10
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "shift logic left";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    //verificar
    else if (opcode == "00001011")// shift lógico p/ direita b.11
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "shift logic right";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    //verificar
    else if (opcode == "00001100")// copia b.12
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "copia";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    //verificar
    else if (opcode == "00001110")// carrega constante de 16 bits nos 2 bytes mais significativos b.13
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "b13 - constante 16 bits nos 2 bytes mais significativos";
        sinaisControle.Memread = 1;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 1;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    //verificar
    else if (opcode == "00001111")// carrega constante de 16 bits nos 2 bytes menos significativos b.14
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "b14 - constante 16 bits nos 2 bytes menos significativos";
        sinaisControle.Memread = 1;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 1;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00010000")// lw b.15
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "load word";
        sinaisControle.Memread = 1;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 1;
        sinaisControle.MemtoReg = 1;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00010001")// sw b.16
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "store word";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 1;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 1;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00010010")// jump and link (jal) b.17
    {                                                      
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "jal";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 1;                             
    }                               
    else if (opcode == "00010011")// jump register (jr) b.18 
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "jr";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 1;
    }
    else if (opcode == "00010100")// jump if equal b.19
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "jump if equal";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 1;
        sinaisControle.Jump = 0;
    }   
    else if (opcode == "00010101")// jump if not-equal b.20
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "jump if not-equal";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 1;
        sinaisControle.Jump = 0;
    }
    else if (opcode == "00010110")// jump incondicional b.21
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "jump inconditional";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 1;
    } 
    //verificar
    else if (opcode == "00010111")// halt b.22
    {
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "halt - saída de sistema";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }


    // Instruções do grupo (9)
    else if (opcode =="00011000"){ // set less than b.23
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "slt";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode =="00011001"){ // set less than immediate b.24
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "slti";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 1;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode =="00011010"){ //smt b.25 (set more than)
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "smt";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    //verificar
    else if (opcode =="00011011"){ //inc b.26 (increment)
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "inc";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    //verificar
    else if (opcode =="00011100"){ // dec b.27 (decrement)
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 0;
        sinaisControle.Aluctrl = "dec";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode =="00011101"){ //addi b.28
        sinaisControle.Regdst = 0;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "addi";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 1;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode =="00011110"){ //subi b.29
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "subi";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 1;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode =="00011111"){ //nand b.30
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "nand";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 0;
        sinaisControle.Alusrc = 10;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
    else if (opcode =="00100000"){ //nor b.31
        sinaisControle.Regdst = 1;
        sinaisControle.Regwrite = 1;
        sinaisControle.Aluctrl = "nor";
        sinaisControle.Memread = 0;
        sinaisControle.Memwrite = 0;
        sinaisControle.Aluop = 10;
        sinaisControle.Alusrc = 0;
        sinaisControle.MemtoReg = 0;
        sinaisControle.Branch = 0;
        sinaisControle.Jump = 0;
    }
}