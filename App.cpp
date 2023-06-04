#include <exception>
#include "codes/Processador.cpp"

int main() {

    Processador *uflaRisc = NULL;

    try{
        uflaRisc = new Processador();

        uflaRisc->executar();

        delete uflaRisc;
    }
    catch(int erro) {
        cout << "ERRO " << erro << "!" << endl;
        switch (erro) {

            case 1:
                cout << "O arquivo não foi encontrado!" << endl;
                break;

            case 2:
                cout << "O valor de address é inválido!" << endl;
                break;

            case 3:
                cout << "A instrução address não é a primeira!" << endl;
                break;

            case 4:
                cout << "O arquivo possui uma instrução inválida!" << endl;
                break;

            case 5:
                cout << "Acesso indevido na memória!" << endl;
                break;

            default:
                cout << "Erro desconhecido encontrado!" << endl;
                break;
        }
    }

    return 0;
}