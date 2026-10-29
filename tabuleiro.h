#ifndef TABULEIRO_H
#define TABULEIRO_H

void configuraTabuleiro();
int valorPosicao(int i, int j);
int verificarJogada(int i, int j);
void desenha();
int temVencedor();
void marcaJogada(int x, int y, int valor);

#endif