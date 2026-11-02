/****
* Implementação do módulo: partida.c
* Autor: Caio Rodrigues Silva
* Data de Criação: 21/10/2026
* Última alteração: 27/10/2026
* Descrição Geral: Administrador da inicialização e sequência de rodadas.
****/

#include <stdio.h>
#include "partida.h"
#include "tabuleiro.h"
#include "t_jogador.h"
#include "jogadorRemoto.h"

void rodarPartidaLocal(t_partidaLocal *partida);
void rodarPartidaRemota(t_partidaRemota *partida);

char decidirTipoPartida() {
	int escolhaTipo;
	printf("Digite 1 para escolher jogo local, ou 2 para escolher jogo remoto: ");
	while (true) {
		scanf(" %d", &escolhaTipo);
		switch (escolhaTipo) {
			case 1:
				return 'L';
				break;
			case 2:
				return 'R';
				break;
			default:
				printf("\nO valor digitado não é válido. Tente novamente: ");
				break;
		}
	}
}

// Decide quem fica com qual símbolo e qual jogador começa
void configuraJogadores(t_partidaLocal *partida) {
	printf("\033[2J\033[H");
	configuraTiposJogadores(&partida->jogador1, &partida->jogador2, &partida->tabuleiro);
	printf("\033[2J\033[H");
	configuraCaracteresJogadores(&partida->jogador1, &partida->jogador2);
}

// Determina o caractere de cada jogador e imprime na tela o tabuleiro
void iniciaLocal() {
	t_partidaLocal partida;

	configuraTabuleiro(&partida.tabuleiro);

	configuraJogadores(&partida);

	desenha(&partida.tabuleiro);

	rodarPartidaLocal(&partida);
}

void rodarPartidaLocal(t_partidaLocal *partida) {
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

/********************
 Bloco partida remota
********************/

void rodarPartidaHost(t_partidaRemota *partida);
void rodarPartidaClient(t_partidaRemota *partida);

void iniciaRemoto() {
	t_partidaRemota partida;

	configuraTabuleiro(&partida.tabuleiro);

	configuraJogadoresRemotos(&partida.jogador1, &partida.jogador2, &partida.tabuleiro);

	if (ehHost(&partida.jogador1))
		hostAccept(&partida.jogador1);
	else
		clientConecta(&partida.jogador1);

	desenha(&partida.tabuleiro);

	if (ehHost(&partida.jogador1))
		rodarPartidaHost(&partida);
	else
		rodarPartidaClient(&partida);
}

void rodarPartidaHost(t_partidaRemota *partida) {
	t_jogadorRemoto jogadorAtual;

	partida->vencedor = 0;
	for (partida->rodada = 1; partida->rodada <= 9; ++partida->rodada) {
		// Alterna entre as rodadas de cada jogador
		switch(partida->rodada % 2) {
			case 0:
				jogadorAtual = partida->jogador1;
				break;
			case 1:
				jogadorAtual = partida->jogador2;
				break;
		}
		jogaRemoto(&jogadorAtual);
	}
}

void rodarPartidaClient(t_partidaRemota *partida) {

}