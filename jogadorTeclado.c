/****
* Implementação do módulo: jogadorTeclado.c
* Autor: Caio Rodrigues Silva
* Data de Criação: 21/10/2026
* Última alteração: 23/10/2026
* Descrição Geral: Interface entre o jogador do teclado e o sistema. Escreve no tabuleiro o valor determinado pelo jogador.
****/

#include <stdio.h>
#include "t_jogador.h"
#include "tabuleiro.h"

void tecladoJoga(t_jogador jogador) {
	int x, y;
	printf("Jogada do %c.\n", jogador.caractere);
	printf("Digite as coordenadas em que deseja jogar no seguinte formato: \"x,y\": ");
	while (1) {
		scanf("%d,%d", &x, &y);

		// Se a jogada for possível.
		if (verificarJogada(x - 1, y - 1)) {
			marcaJogada(x - 1, y - 1, jogador.valor);
			break;
		}
		// Se a jogada não for possível.
		else {
			printf("Essa posição não é válida, digite novamente: ");
		}
	}
}
