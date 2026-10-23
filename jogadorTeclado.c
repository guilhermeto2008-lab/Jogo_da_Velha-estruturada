#include <stdio.h>
#include "t_jogador.h"
#include "tabuleiro.h"

void joga() {
	printf("Digite as coordenadas em que deseja jogar no seguinte formato: \"x,y\": ");
	while (1) {
		scanf("%hd,%hd", &x, &y);

		if (verificarJogada(x - 1, y - 1)) {
			marcaJogada(x - 1, y - 1, valorJogador);
			break;
		}
		else {
			printf("Essa posição não é válida, digite novamente: ");
		}
	}
}
