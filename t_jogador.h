#ifndef JOGADOR_H
#define JOGADOR_H

#include "tabuleiro.h"

typedef struct {
	int tipo;
	int valor;
	char caractere;
	t_tabuleiro *copiaTabuleiro;
} t_jogador;

void configuraTiposJogadores(t_jogador *jogador1, t_jogador *jogador2, t_tabuleiro *tabuleiro);
void configuraCaracteresJogadores(t_jogador *jogador1, t_jogador *jogador2);
void joga(t_jogador *jogador);

#endif
