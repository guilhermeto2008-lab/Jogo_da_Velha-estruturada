#ifndef JOGADOR_H
#define JOGADOR_H

#include "tabuleiro.h"

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

/*
Tipos:
3 = host
4 = client
*/
typedef struct {
	int tipo;
	int valor;
	char caractere;
	t_tabuleiro *copiaTabuleiro;
	int socketfd;
} t_jogadorRemoto;

void configuraTiposJogadores(t_jogador *jogador1, t_jogador *jogador2, t_tabuleiro *tabuleiro);
void configuraCaracteresJogadores(t_jogador *jogador1, t_jogador *jogador2);
void joga(t_jogador *jogador);

void configuraJogadoresRemotos(t_jogadorRemoto *jogador1, t_jogadorRemoto *jogador2, t_tabuleiro *tabuleiro);
int ehHost(t_jogadorRemoto *jogador);
void jogaRemoto(t_jogadorRemoto *jogador);

#endif
