// Trabalho Prático 1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <speechapi_cxx.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <dos.h>
#include<windows.h>
#include <locale.h>
#include <string>

using std::string;
using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;
auto config = SpeechConfig::FromSubscription("b0619ea6cfae4a5ab0bb8841996fd84f", "brazilsouth");
auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
auto recognizer = SpeechRecognizer::FromConfig(config, audioConfig);
auto synthesizer = SpeechSynthesizer::FromConfig(config);


int matriz[3][3];
string oponente;
string pc = "Computador.";
string jogador = "Jogador.";

//Procedimento inicializa todas as posições do jogo da velha com '0'
void inicializa() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matriz[i][j] = 0;
        }
    }
}

//Procedimento para o jogador 1 escolher a posição desejada, substitui na matriz o elemento '0' por '1'
void PlayerJogar() {
    int l, c;
    do {
        cout << "Jogador 1" << endl;
        cout << "Digite a linha desejada." << endl;
        cin >> l;
        cout << "Digite a coluna desejada." << endl;
        cin >> c;
        cout << endl;
        if (matriz[l - 1][c - 1] != 0) {
            cout << "Posição já escolhida. Tente outra posição." << endl;
        }
    } while (matriz[l - 1][c - 1] != 0);
    matriz[l-1][c-1]=1;
}

//Procedimento para o jogador 2 escolher a posição desejada, substitui na matriz o elemento '0' por '2'
void Player2Jogar() {
    int l, c;
    do {
        cout << "Jogador 2" << endl;
        cout << "Digite a linha desejada." << endl;
        cin >> l;
        cout << "Digite a coluna desejada." << endl;
        cin >> c;
        cout << endl;
        if (matriz[l - 1][c - 1] != 0) {
            cout << "Posição já escolhida. Tente outra posição." << endl;
        }
    } while (matriz[l - 1][c - 1] != 0);
    matriz[l - 1][c - 1] = 2;
}

//Procedimento para o oponente 'PC' escolher uma posição aleatória, , substitui na matriz o elemento '0' por '2'
void PCJogar() {
    cout << "PC jogando";
    for (int i = 1; i <= 3; i++) {
        cout << ".";
        Sleep(1000);
    }
    cout << endl;
    int l, c;
    do {
        srand(time(0));
        l = rand() % 3;
        c = rand() % 3;
    } while (matriz[l][c] != 0);
    cout << endl;
    matriz[l][c] = 2;
}

//Procedimento imprime o jogo da velha
void imprimeMatriz() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            cout << matriz[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
}

//Procedimento recebe uma string como parâmetro e transforma essa string em audio
void falar(string t) {
    config->SetSpeechSynthesisLanguage("pt-BR");
    synthesizer = SpeechSynthesizer::FromConfig(config);
    synthesizer->SpeakTextAsync(t).get();
}

//Função checa o estado atual do jogo, se for encontrada uma condição de vitória, retorna 1 ou 2, caso haja um vencedor, ou retorna -1 se não houver vencedor
int checarJogo() {
    int end = 0;
    for (int i = 0; i < 3; i++) {
        if (matriz[i][0] == matriz[i][1] && matriz[i][1] == matriz[i][2] && matriz[i][2]==1) {
            return 1;
        }
        if (matriz[i][0] == matriz[i][1] && matriz[i][1] == matriz[i][2] && matriz[i][2] == 2) {
            return 2;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (matriz[0][i] == matriz[1][i] && matriz[1][i] == matriz[2][i] && matriz[0][i] == 1) {
            return 1;
        }
        if (matriz[0][i] == matriz[1][i] && matriz[1][i] == matriz[2][i] && matriz[0][i] == 2) {
            return 2;
        }
    }

    if (matriz[1][1] == matriz[2][2] && matriz[2][2] == matriz[3][3] && matriz[1][1] == 1) {
        return 1;
    }

    if (matriz[1][1] == matriz[2][2] && matriz[2][2] == matriz[3][3] && matriz[1][1] == 2) {
        return 2;
    }

    if (matriz[1][3] == matriz[2][2] && matriz[2][2] == matriz[3][1] && matriz[1][3] == 1) {
        return 1;
    }
    if (matriz[1][3] == matriz[2][2] && matriz[2][2] == matriz[3][1] && matriz[1][3] == 2) {
        return 2;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matriz[i][j] != 0) {
                end++;
            }   
        }
    }
    if (end == 9) {
        return -1;
    }
    return 0;
}

//Função recebe audio do microfone padrão e transforma-o em string
string ouvir() {
    config->SetSpeechRecognitionLanguage("pt-BR");
    recognizer = SpeechRecognizer::FromConfig(config, audioConfig);
    auto result = recognizer->RecognizeOnceAsync().get();
    return result->Text;
}

//Procedimento contem todo codigo, funções e procedimentos do jogo
void game() {
    do {
        int l, c;
        imprimeMatriz();
        PlayerJogar();
        imprimeMatriz();
        if (checarJogo() == 1) {
            cout << "O jogador foi o vencedor" << endl;
            falar("Parabéns, voce ganhou.");
            break;
        }
        else if (checarJogo() == 2) {
            cout << "O jogador 2 foi o vencedor" << endl;
            break;
        }
        else if (checarJogo() == -1) {
            cout << "Não houve vencedor nessa partida." << endl;
            break;
        }
        if (oponente == pc) {
            PCJogar();
        }
        else if (oponente == jogador) {
            Player2Jogar();
        }
        if (checarJogo() == 1) {
            cout << "O jogador foi o vencedor" << endl;
            falar("Parabéns, voce ganhou.");
            break;
        }
        else if (checarJogo() == 2) {
            cout << "O oponente foi o vencedor" << endl;
            break;
        }
        else if (checarJogo() == -1) {
            cout << "Não houve vencedor nessa partida." << endl;
            break;
        }
        
    } while (checarJogo() == 0);
}

//Função possui o código para inicializar o jogo
int menu() {
    setlocale(LC_ALL, "Portuguese");
    cout << "Bem-vindo ao Jogo da Velha!" << endl;
    int in;
    do {
        in = 0;
        cout << "Diga 'jogar' para iniciar o jogo ou 'sair' para sair." << endl;
        string opcao = ouvir();
        string jogar = "Jogar.";
        string sair = "Sair.";
        if (opcao == sair) {
            return 0;
        }
        else if (opcao == jogar) {
            cout << "Escolha seu oponente:" << endl;
            do{
                cout << "Diga 'computador' para jogar contra o PC ou 'jogador' para jogar com outra pessoa." << endl;
                oponente = ouvir();
                if (oponente != pc && oponente != jogador) {
                    falar("opção inválida");
                    continue;
                }
                falar("O jogo já vai começar");
                inicializa();
                game();
            } while (oponente != pc && oponente != jogador);
        }
        else {
            in = 1;
            falar("opção inválida.");
        }
    } while (in==1);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    menu();

}
