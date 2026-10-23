#include <stdio.h>
#include "tabuleiro.h"
#include "t_jogador.h"
#include "jogadorTeclado.h"

typedef struct {
	short int rodada;
	t_jogador jogador1;
	t_jogador jogador2;
} t_partida;

static t_partida partida;

// Decide quem fica com qual símbolo e qual jogador começa
void configuraJogadores() {
	// TODO: Colocar a parte de escolher jogador real, IA ou socket
	char escolha;

	// Configura o primeiro jogador
	printf("O jogador 1 ficará com qual caractere? Digite 'X' ou 'O'.\n> ");

	while (partida.jogador1.caractere != 'X' || partida.jogador2.caractere != 'O') {
		scanf("%c", &escolha);
		switch (escolha) {
			case 'O':
				partida.jogador1.caractere = escolha;
				break;
			case 'X':
				partida.jogador1.caractere = escolha;
				break;
			default:
				printf("O valor digitado não é válido. Tente novamente: ");
				break;
		}
	}
}

// Determina o caractere de cada jogador e imprime na tela o tabuleiro
void inicia() {
	configuraJogadores();

	limparTabuleiro();

	desenha();

	joga();
}
