#ifndef JOGADORREMOTO_H
#define JOGADORREMOTO_H

#include "t_jogador.h"

void configuraJogadoresRemotos(t_jogadorRemoto *jogador, t_tabuleiro *tabuleiro);

void remotoJoga(t_jogadorRemoto *jogador);
void conecta(t_jogadorRemoto *jogador);
void enviaJogada(t_jogadorRemoto *jogador, int x, int y, int valor);
void recebeJogada(t_jogadorRemoto *jogador);

#endif