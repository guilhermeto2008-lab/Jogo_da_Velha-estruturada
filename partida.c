#include <stdio.h>
#include "tabuleiro.h"
#include "t_jogador.h"

typedef struct {
	int rodada;
	t_jogador jogador1;
	t_jogador jogador2;
} t_partida;

static t_partida partida;

void rodarPartida();

// Decide quem fica com qual símbolo e qual jogador começa
void configuraJogadores() {
	printf("\033[2J\033[H");
	configuraTiposJogadores(&partida.jogador1, &partida.jogador2);
	printf("\033[2J\033[H");
	configuraCaracteresJogadores(&partida.jogador1, &partida.jogador2);
}

// Determina o caractere de cada jogador e imprime na tela o tabuleiro
void inicia() {
	zerarTabuleiro();

	configuraJogadores();

	desenha();

	rodarPartida();
}

void rodarPartida() {
	int rodada, vencedor;

	t_jogador jogadorAtual;

	// For das 9 rodadas do jogo
	for (rodada = 1; rodada <= 9; ++rodada) {

		// Jogada dos jogadores
		if (rodada % 2 == 1)
			jogadorAtual = partida.jogador1;
		else
			jogadorAtual = partida.jogador2;
		joga(jogadorAtual);

		// Verifica se alguém ganhou
		if (rodada >= 5) {
			if (temVencedor()) {
				vencedor = temVencedor();
				break;
			}
		}

		desenha();
	}

	// Printa o vencedor
	if (vencedor == partida.jogador1.valor)
		printf("O %c venceu.\n", partida.jogador1.caractere);
	else if (vencedor == partida.jogador2.valor)
		printf("O %c venceu.\n", partida.jogador2.caractere);
	else
		puts("Deu velha.");
}
