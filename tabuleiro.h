#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef struct {
	int M[3][3];
} t_tabuleiro;

t_tabuleiro acessarTabuleiro();
void zerarTabuleiro();
int verificarJogada(short int x, short int y);
void desenha();
int temVencedor();
int marcaJogada();

#endif
