#include "Memoria.cpp"

class Conversor {

    private:
        int enderecoComecoMemoriaTexto;
        Memoria *memoria;

        void leituraArquivoEntrada();
        bool encontrarAddress(string instrucaoAtual);
        int conversorBinario(char bin[], int tamVet);

    public:
        Conversor();
        ~Conversor();
        int getEnderecoComecoMemmoriaTexto();
        Memoria* getMemoria();
};

Conversor::Conversor() {

    enderecoComecoMemoriaTexto = 0;
    memoria = new Memoria();

    leituraArquivoEntrada();
}

Conversor::~Conversor() {

    delete memoria;
}

void Conversor::leituraArquivoEntrada() {

    string nome_arquivo_entrada;

    cout << "Digite o nome do arquivo de entrada de instruções (sem extensão): ";
    cin >> nome_arquivo_entrada;

    ifstream arquivo_entrada("files/" + nome_arquivo_entrada + ".txt");

    if(arquivo_entrada) {

        string instrucaoAtual;
        bool addressLido = false, primeiraLeitura = false;
        int enderecoMemoriaTexto = enderecoComecoMemoriaTexto;

        do {

            // leitura uma instrucao (ou de um "address")
		    getline(arquivo_entrada, instrucaoAtual);

            if(!primeiraLeitura and !addressLido) {

                primeiraLeitura = true;

                addressLido = encontrarAddress(instrucaoAtual);

                enderecoMemoriaTexto = enderecoComecoMemoriaTexto;

                if(addressLido){

                    continue;
                }
            }

            // registro da instrucao na memoria
            memoria->armazenarInstrucao(instrucaoAtual, enderecoMemoriaTexto);
            enderecoMemoriaTexto++;

        } while(instrucaoAtual != "11111111111111111111111111111111");

        arquivo_entrada.close();
    }

    else {

        // FAZER ERRO
    }
}

// tenta achar se "address" foi escrito
bool Conversor::encontrarAddress(string instrucaoAtual) {

    char espaco = ' ';
	size_t found_esp = instrucaoAtual.find(espaco);

    // achou
	if(found_esp != string::npos){
        
        // encontra-se o tamanho do binario do endereco da memoria de texto
        int tamanhoBinEnderecoMemoriaTexto = instrucaoAtual.size() - found_esp - 1;
        char enderecoMemoriaTexto_Char[tamanhoBinEnderecoMemoriaTexto];

        // enderecoMemoriaTexto_Char recebe a string apenas com o binario
        for(int i = 0; i < tamanhoBinEnderecoMemoriaTexto; i++) {

            enderecoMemoriaTexto_Char[i] = instrucaoAtual[found_esp + 1 + i];
        }

        int aux = conversorBinario(enderecoMemoriaTexto_Char, tamanhoBinEnderecoMemoriaTexto);

        if(aux >= pow(2, adressBus) or aux < 0) {

            // FAZER ERRO

            return false;
        }

        else {

            enderecoComecoMemoriaTexto = aux;

            return true;
        }
	}

    return false;
}

// converte o endereco binario para int
int Conversor::conversorBinario(char bin[], int tamVet) {

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

int Conversor::getEnderecoComecoMemmoriaTexto() {

    return enderecoComecoMemoriaTexto;
}

Memoria* Conversor::getMemoria() {

    return memoria;
}
