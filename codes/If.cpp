class If {

    private:
        string registradorInstrucoes;
        int PC;
        bool addressLido;
        int linhaAtual;
        bool encontrarAddress();
        int conversorBinario(char bin[], int tamVet);

    public:
        If();
        ~If();
        void executar(string input);
        string getInstrucao();
};

If::If() {

    PC = 0;
    addressLido = false;
    linhaAtual = 0;
}

If::~If() {


}

string If::getInstrucao(){

    return registradorInstrucoes;
}

void If::executar(string input) {

    ifstream arquivo_entrada("files/" + input + ".txt");

    if(arquivo_entrada) {

        // "abre" o arquivo em uma linha especifica
        for(int i = 0; i < linhaAtual; i++) {

            string lixo;

            getline(arquivo_entrada, lixo);
        }

        // leitura uma instrucao (ou de um "address")
		getline(arquivo_entrada, registradorInstrucoes);
        linhaAtual++;

        if(!addressLido) {

            addressLido = encontrarAddress();
        }

        arquivo_entrada.close();
    }
}

bool If::encontrarAddress() {

    // tenta achar se "address" foi escrito
    char espaco = ' ';
	size_t found_esp = registradorInstrucoes.find(espaco);

    // achou
	if(found_esp != string::npos){
        
        // encontra-se o tamanho do binario do endereco da memoria de texto
        int tamanhoBinEnderecoMemoriaTexto = registradorInstrucoes.size() - found_esp - 1;
        char enderecoMemoriaTexto_Char[tamanhoBinEnderecoMemoriaTexto];

        // enderecoMemoriaTexto_Char recebe a string apenas com o binario
        for(int i = 0; i < tamanhoBinEnderecoMemoriaTexto; i++) {

            enderecoMemoriaTexto_Char[i] = registradorInstrucoes[found_esp + 1 + i];
        }

        int aux = conversorBinario(enderecoMemoriaTexto_Char, tamanhoBinEnderecoMemoriaTexto);

        if(aux >= pow(2, adressBus) or aux < 0) {

            // FAZER ERRO
        }

        else {

            PC = aux;

            return true;
        }
	}

    return false;
}

// converte o endereco binario para int
int If::conversorBinario(char bin[], int tamVet) {

    int retorno = 0;
	int potencia_dois = 1;
	
	for(int i = tamVet; i > 0; i--){
		
		if(bin[i - 1] == '1') {

            retorno += potencia_dois;
        }

		potencia_dois *= 2;
	}
	
	return retorno;
}