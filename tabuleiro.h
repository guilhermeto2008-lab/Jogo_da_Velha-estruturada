#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef struct {
	int M[3][3];
} t_tabuleiro;

t_tabuleiro acessarTabuleiro();
void configuraTabuleiro();
int verificarJogada(int x, int y);
void desenha();
int temVencedor();
void marcaJogada(int x, int y, int valor);

#endif