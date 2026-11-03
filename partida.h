#ifndef PARTIDA_H
#define PARTIDA_H

#include "tabuleiro.h"
#include "t_jogador.h"
#include "jogadorRemoto.h"

typedef struct {
	t_tabuleiro tabuleiro;
	int rodada;
	t_jogador jogador1;
	t_jogador jogador2;
	int vencedor;
} t_partidaLocal;

typedef struct {
	t_tabuleiro tabuleiro;
	int rodada;
	t_jogadorRemoto jogador;
	int vencedor;
} t_partidaRemota;

// Retorna 'L' para local e 'R' para remoto
char decidirTipoPartida();
void iniciaLocal();
void iniciaRemoto();

#endif
