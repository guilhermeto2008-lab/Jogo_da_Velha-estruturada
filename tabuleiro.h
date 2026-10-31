#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef struct {
	int M[3][3];
} t_tabuleiro;

void configuraTabuleiro(t_tabuleiro *tabuleiro);
int verificarJogada(t_tabuleiro *tabuleiro, int i, int j);
void desenha(t_tabuleiro *tabuleiro);
int temVencedor(t_tabuleiro *tabuleiro);
int acessarTabuleiro(t_tabuleiro *tabuleiro, int i, int j);
void marcaJogada(t_tabuleiro *tabuleiro, int i, int j, int valor);

#endif