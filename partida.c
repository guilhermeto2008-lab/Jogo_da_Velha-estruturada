/****
* Implementação do módulo: partida.c
* Autor: Caio Rodrigues Silva
* Data de Criação: 21/10/2026
* Última alteração: 27/10/2026
* Descrição Geral: Administrador da inicialização e sequência de rodadas.
****/

#include <stdio.h>
#include "tabuleiro.h"
#include "t_jogador.h"

typedef struct {
	int rodada;
	t_jogador jogador1;
	t_jogador jogador2;
	int vencedor;
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
	configuraTabuleiro();

	configuraJogadores();

	desenha();

	rodarPartida();
}

void rodarPartida() {
	t_jogador jogadorAtual;

	partida.vencedor = 0;
	// For das 9 rodadas do jogo
	for (partida.rodada = 1; partida.rodada <= 9; ++partida.rodada) {

		// Jogada dos jogadores
		switch (partida.rodada % 2) {
			case 1:
				jogadorAtual = partida.jogador1;
				break;
			case 0:
				jogadorAtual = partida.jogador2;
				break;
		}
		joga(jogadorAtual);

		// Verifica se alguém ganhou
		if (partida.rodada >= 5) {
			if (temVencedor()) {
				desenha();
				partida.vencedor = temVencedor();
				break;
			}
		}

		desenha();
	}

	// Printa o vencedor
	if (partida.vencedor == partida.jogador1.valor)
		printf("O %c venceu.\n", partida.jogador1.caractere);
	else if (partida.vencedor == partida.jogador2.valor)
		printf("O %c venceu.\n", partida.jogador2.caractere);
	else
		puts("Deu velha.");
}
