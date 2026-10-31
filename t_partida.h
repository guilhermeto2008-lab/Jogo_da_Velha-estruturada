#include "tabuleiro.h"
#include "t_jogador.h"

typedef struct {
	t_tabuleiro tabuleiro;
	int rodada;
	t_jogador jogador1;
	t_jogador jogador2;
	int vencedor;
} t_partida;