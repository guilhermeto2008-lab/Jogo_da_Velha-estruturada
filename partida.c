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

void rodarPartida();

// Decide quem fica com qual símbolo e qual jogador começa
void configuraJogadores() {
	// Jogador 1 sempre será um jogador de teclado
	partida.jogador1.tipo = 1;

	short int escolhaTipo;
	printf("Digite 1 para o modo jogador contra jogador, 2 para o modo jogador contra IA e 3 para jogador contra jogador online: ");
	while (partida.jogador2.tipo != 1 && partida.jogador2.tipo != 2 && partida.jogador2.tipo != 3) {
		scanf("%hd", &escolhaTipo);
		switch (escolhaTipo) {
			case 1:
				partida.jogador2.tipo = 1;
				break;
			case 2:
				partida.jogador2.tipo = 2;
				break;
			case 3:
				partida.jogador2.tipo = 3;
				break;
			default:
				printf("O valor digitado não é válido. Tente novamente: ");
				break;
		}
	}
	
	char escolhaCaractere;
	// Configura o caractere dos jogadores
	printf("O jogador 1 ficará com qual caractere? Digite 'X' ou 'O': ");

	while (partida.jogador1.caractere != 'X' && partida.jogador2.caractere != 'O') {
		scanf(" %c", &escolhaCaractere);
		switch (escolhaCaractere) {
			case 'O':
				partida.jogador1.caractere = 'O';
				partida.jogador1.valor = 1;
				partida.jogador2.caractere = 'X';
				partida.jogador2.valor = 4;
				break;
			case 'X':
				partida.jogador1.caractere = 'X';
				partida.jogador1.valor = 4;
				partida.jogador2.caractere = 'O';
				partida.jogador2.valor = 1;
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

	rodarPartida();
}

void rodarPartida() {
	short int rodada, vencedor;

	// For das 9 rodadas do jogo
	for (rodada = 1; rodada <= 9; ++rodada) {

		// Jogada dos jogadores
		if (rodada % 2 == 1)
			joga(&partida.jogador1);
		else
			joga(&partida.jogador2);

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
	if (vencedor == 0)
		puts("Deu velha.");
	else if (vencedor == 1)
		printf("O %c venceu.\n", partida.jogador1.caractere);
	else if (vencedor == 4)
		printf("O %c venceu.\n", partida.jogador2.caractere);
}
