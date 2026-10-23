#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct {
	short int x, y;
	short int valor;
} t_jogada;

typedef struct {
	short int tipo;
	short int valor;
	char caractere;
	t_jogada jogada;
} t_jogador;

#endif
