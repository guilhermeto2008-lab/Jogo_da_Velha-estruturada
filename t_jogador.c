/****
* Implementação do módulo: t_jogador.c
* Autor: Caio Rodrigues Silva
* Data de Criação: 23/10/2026
* Última alteração: 27/10/2026
* Descrição Geral: Intermediário entre a partida e os diversos tipos de jogadores.
				Oferece todas as operações referentes a jogadores sem necessidade de conhecimento do partida.c
****/

#include <stdio.h>
#include "t_jogador.h"
#include "jogadorTeclado.h"
#include "jogadorIA.h"

void configuraTiposJogadores(t_jogador *jogador1, t_jogador *jogador2) {
	// Jogador 1 sempre será um jogador de teclado
	jogador1->tipo = 1;

	// Configura se vai ser jogador x jogador, jogador x IA ou por socket.
	int escolhaTipo;
	printf("Digite 1 para o modo jogador contra jogador, 2 para o modo jogador contra IA e 3 para jogador contra jogador online: ");
	while (jogador2->tipo != 1 && jogador2->tipo != 2 && jogador2->tipo != 3) {
		scanf("%d", &escolhaTipo);
		switch (escolhaTipo) {
			case 1:
				jogador2->tipo = 1;
				break;
			case 2:
				jogador2->tipo = 2;
				break;
			case 3:
				jogador2->tipo = 3;
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


void joga(t_jogador jogador) {
	if (jogador.tipo == 1)
		tecladoJoga(jogador);
	else if (jogador.tipo == 2)
		iaJoga(jogador);
}
