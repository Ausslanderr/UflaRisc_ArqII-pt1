#include <iostream>
#include <math.h>
#include <fstream>
#include <bitset>

#define dataBus 32
#define adressBus 16

using namespace std;

#include "Memoria.cpp"
#include "If.cpp"
#include "Id.cpp"
#include "ExMem.cpp"
#include "Wb.cpp"

class Processador {

    private:
        Memoria *memoria;
        If *ifStage;
        //Id *idStage;
        //ExMem *exMemStage;
        //Wb *wbStage;
        int qtdClocks;
        int leituraArquivoEntrada();
        bool encontrarAddress(string instrucaoAtual, int &enderecoComemoMemoriaTexto);
        int conversorBinario(char bin[], int tamVet);
        void incrementarClock();

    public:
        Processador();
        ~Processador();
        void executar();
};

Processador::Processador() {

    memoria = new Memoria();
    //idStage = new Id();
    //exMemStage = new ExMem();
    //wbStage = new Wb();

    qtdClocks = 0;
}

Processador::~Processador() {

    delete memoria;
    delete ifStage;
    //delete idStage;
    //delete exMemStage;
    //delete wbStage;
}

void Processador::executar() {

    int PC = leituraArquivoEntrada();

    ifStage = new If(memoria, PC);

    cout << ifStage->getInstrucao() << endl;
    incrementarClock();
    cout << ifStage->getInstrucao() << endl;
    incrementarClock();

    cout << qtdClocks << endl;
}

int Processador::leituraArquivoEntrada() {

    string nome_arquivo_entrada;

    cout << "Digite o nome do arquivo de entrada de instruções (sem extensão): ";
	cin >> nome_arquivo_entrada;

    ifstream arquivo_entrada("files/" + nome_arquivo_entrada + ".txt");

    if(arquivo_entrada) {

        string instrucaoAtual;
        bool addressLido = false, primeiraLeitura = false;
        int enderecoComecoMemoriaTexto = 0, enderecoMemoriaTexto = enderecoComecoMemoriaTexto;

        do {

            // leitura uma instrucao (ou de um "address")
		    getline(arquivo_entrada, instrucaoAtual);

            if(!primeiraLeitura and !addressLido) {

                primeiraLeitura = true;

                addressLido = encontrarAddress(instrucaoAtual, enderecoComecoMemoriaTexto);

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

        return enderecoComecoMemoriaTexto;
    }

    else {

        // FAZER ERRO

        return -1;
    }
}

// tenta achar se "address" foi escrito
bool Processador::encontrarAddress(string instrucaoAtual, int &enderecoComemoMemoriaTexto) {

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

            enderecoComemoMemoriaTexto = aux;

            return true;
        }
	}

    return false;
}

// converte o endereco binario para int
int Processador::conversorBinario(char bin[], int tamVet) {

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

void Processador::incrementarClock() {

    qtdClocks++;
}