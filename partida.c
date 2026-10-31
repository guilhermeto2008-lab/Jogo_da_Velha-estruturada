/****
* Implementação do módulo: partida.c
* Autor: Caio Rodrigues Silva
* Data de Criação: 21/10/2026
* Última alteração: 27/10/2026
* Descrição Geral: Administrador da inicialização e sequência de rodadas.
****/

#include <stdio.h>
#include "t_partida.h"
#include "tabuleiro.h"
#include "t_jogador.h"

void rodarPartida(t_partida *partida);

// Decide quem fica com qual símbolo e qual jogador começa
void configuraJogadores(t_partida *partida) {
	printf("\033[2J\033[H");
	configuraTiposJogadores(&partida->jogador1, &partida->jogador2, &partida->tabuleiro);
	printf("\033[2J\033[H");
	configuraCaracteresJogadores(&partida->jogador1, &partida->jogador2);
}

// Determina o caractere de cada jogador e imprime na tela o tabuleiro
void inicia() {
	t_partida partida;

	configuraTabuleiro(&partida.tabuleiro);

	configuraJogadores(&partida);

	desenha(&partida.tabuleiro);

	rodarPartida(&partida);
}

void rodarPartida(t_partida *partida) {
	t_jogador jogadorAtual;

	partida->vencedor = 0;
	// For das 9 rodadas do jogo
	for (partida->rodada = 1; partida->rodada <= 9; ++partida->rodada) {

		// Jogada dos jogadores
		switch (partida->rodada % 2) {
			case 1:
				jogadorAtual = partida->jogador1;
				break;
			case 0:
				jogadorAtual = partida->jogador2;
				break;
		}
		joga(&jogadorAtual);

		// Verifica se alguém ganhou
		if (partida->rodada >= 5) {
			if (temVencedor(&partida->tabuleiro)) {
				desenha(&partida->tabuleiro);
				partida->vencedor = temVencedor(&partida->tabuleiro);
				break;
			}
		}

		desenha(&partida->tabuleiro);
	}

	// Printa o vencedor
	if (partida->vencedor == partida->jogador1.valor)
		printf("O %c venceu.\n", partida->jogador1.caractere);
	else if (partida->vencedor == partida->jogador2.valor)
		printf("O %c venceu.\n", partida->jogador2.caractere);
	else
		puts("Deu velha.");
}
