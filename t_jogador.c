/****
* Implementação do módulo: t_jogador.c
* Autor: Caio Rodrigues Silva
* Data de Criação: 23/10/2026
* Última alteração: 27/10/2026
* Descrição Geral: Intermediário entre a partida e os diversos tipos de jogadores.
				Oferece todas as operações referentes a jogadores sem necessidade de conhecimento do partida.c
****/

#include <stdio.h>
#include <arpa/inet.h>
#include "t_jogador.h"
#include "jogadorTeclado.h"
#include "jogadorIA.h"
#include "jogadorRemoto.h"

void configuraTiposJogadores(t_jogador *jogador1, t_jogador *jogador2, t_tabuleiro *tabuleiro) {
	jogador1->copiaTabuleiro = tabuleiro;
	jogador2->copiaTabuleiro = tabuleiro;
	
	// Jogador 1 sempre será um jogador de teclado
	jogador1->tipo = 1;

	// Configura se vai ser jogador x jogador, jogador x IA ou por socket.
	int escolhaTipo;
	printf("Digite 1 para o modo jogador contra jogador e 2 para o modo jogador contra IA: ");
	while (1) {
		scanf("%d", &escolhaTipo);
		switch (escolhaTipo) {
			case 1:
				jogador2->tipo = 1;
				return;
				break;
			case 2:
				jogador2->tipo = 2;
				return;
				break;
			default:
				printf("\nO valor digitado não é válido. Tente novamente: ");
				break;
		}
	}
}

void configuraCaracteresJogadores(t_jogador *jogador1, t_jogador *jogador2) {
	// Configura o caractere dos jogadores
	char escolhaCaractere;
	printf("O jogador 1 ficará com qual caractere? Digite 'X' ou 'O': ");

	while (jogador1->caractere != 'X' && jogador2->caractere != 'O') {
		scanf(" %c", &escolhaCaractere);
		switch (escolhaCaractere) {
			case 'O':
				jogador1->caractere = 'O';
				jogador1->valor = 1;
				jogador2->caractere = 'X';
				jogador2->valor = 4;
				break;
			case 'X':
				jogador1->caractere = 'X';
				jogador1->valor = 4;
				jogador2->caractere = 'O';
				jogador2->valor = 1;
				break;
			default:
				printf("\nO valor digitado não é válido. Tente novamente: ");
				break;
		}
	}
}

void joga(t_jogador *jogador) {
	if (jogador->tipo == 1)
		tecladoJoga(jogador);
	else if (jogador->tipo == 2)
		iaJoga(jogador);
}

/********************
 Bloco jogador remoto
********************/

void configuraJogadoresRemotos(t_jogadorRemoto *jogador1, t_jogadorRemoto *jogador2, t_tabuleiro *tabuleiro) {
	jogador1->copiaTabuleiro = tabuleiro;
	jogador2->copiaTabuleiro = tabuleiro;

	jogador1->socketfd = socket(AF_INET, SOCK_STREAM, 0);
	jogador2->socketfd = socket(AF_INET, SOCK_STREAM, 0);

	// Configura se vai ser jogador x jogador, jogador x IA ou por socket.
	int escolhaTipo;
	printf("Digite 1 para hostear o jogo e 2 para se conectar a outro jogo: ");
	while (1) {
		scanf("%d", &escolhaTipo);
		switch (escolhaTipo) {
			case 1:
				jogador1->tipo = 3;
				jogador2->tipo = 4;
				return;
				break;
			case 2:
				jogador1->tipo = 4;
				jogador2->tipo = 3;
				return;
				break;
			default:
				printf("\nO valor digitado não é válido. Tente novamente: ");
				break;
		}
	}
}

int ehHost(t_jogadorRemoto *jogador) {
	switch (jogador->tipo) {
		case 3:
			return 1;
			break;
		case 4:
			return 0;
			break;
	}
}

void jogaRemoto(t_jogadorRemoto *jogador) {
	if (jogador->tipo == 3)
		hostJoga(jogador);
	else if (jogador->tipo == 4)
		clientJoga(jogador);
}