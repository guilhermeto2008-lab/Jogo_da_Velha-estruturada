#ifndef JOGADOR_H
#define JOGADOR_H

#include "tabuleiro.h"
#include "configRemoto.h"

/*
Tipos:
1 = teclado
2 = IA
*/
typedef struct {
	int tipo;
	int valor;
	char caractere;
	t_tabuleiro *copiaTabuleiro;
} t_jogador;

typedef struct {
	int ehHost;
	int valor;
	char caractere;
	t_tabuleiro *copiaTabuleiro;
	int servidor_fd;
	int cliente_fd;
	int buffer[TAM_BUFFER];
} t_jogadorRemoto;

#endif
