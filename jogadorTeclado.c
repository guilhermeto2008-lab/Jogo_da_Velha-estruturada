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
