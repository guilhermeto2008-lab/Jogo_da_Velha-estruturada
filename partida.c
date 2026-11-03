/****
* Implementação do módulo: partida.c
* Autor: Caio Rodrigues Silva
* Data de Criação: 21/10/2026
* Última alteração: 27/10/2026
* Descrição Geral: Administrador da inicialização e sequência de rodadas.
****/

#include <stdio.h>
#include <unistd.h>
#include "partida.h"
#include "tabuleiro.h"
#include "t_jogador.h"
#include "jogadorTeclado.h"
#include "jogadorIA.h"
#include "jogadorRemoto.h"

void rodarPartidaLocal(t_partidaLocal *partida);

char decidirTipoPartida() {
	int escolhaTipo;
	printf("Digite 1 para escolher jogo local, ou 2 para escolher jogo remoto: ");
	while (1) {
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
	partida->jogador1.copiaTabuleiro = &partida->tabuleiro;
	partida->jogador2.copiaTabuleiro = &partida->tabuleiro;
	
	// Jogador 1 sempre será um jogador de teclado
	partida->jogador1.tipo = 1;
	partida->jogador2.tipo = 0;

	// Configura se vai ser jogador x jogador, jogador x IA ou por socket.
	int escolhaTipo;
	printf("Digite 1 para o modo jogador contra jogador e 2 para o modo jogador contra IA: ");
	while (partida->jogador2.tipo == 0) {
		scanf("%d", &escolhaTipo);
		switch (escolhaTipo) {
			case 1:
				partida->jogador2.tipo = 1;
				break;
			case 2:
				partida->jogador2.tipo = 2;
				break;
			default:
				printf("\nO valor digitado não é válido. Tente novamente: ");
				break;
		}
	}

	printf("\033[2J\033[H");

	// Configura o caractere dos jogadores
	char escolhaCaractere;
	printf("O jogador 1 ficará com qual caractere? Digite 'X' ou 'O': ");

	while (partida->jogador1.caractere != 'X' && partida->jogador2.caractere != 'O') {
		scanf(" %c", &escolhaCaractere);
		switch (escolhaCaractere) {
			case 'O':
				partida->jogador1.caractere = 'O';
				partida->jogador1.valor = 1;
				partida->jogador2.caractere = 'X';
				partida->jogador2.valor = 4;
				break;
			case 'X':
				partida->jogador1.caractere = 'X';
				partida->jogador1.valor = 4;
				partida->jogador2.caractere = 'O';
				partida->jogador2.valor = 1;
				break;
			default:
				printf("\nO valor digitado não é válido. Tente novamente: ");
				break;
		}
	}

	printf("\033[2J\033[H");
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
	t_jogador *jogadorAtual;

	partida->vencedor = 0;
	// For das 9 rodadas do jogo
	for (partida->rodada = 1; partida->rodada <= 9; ++partida->rodada) {

		// Jogada dos jogadores
		switch (partida->rodada % 2) {
			case 1:
				jogadorAtual = &partida->jogador1;
				break;
			case 0:
				jogadorAtual = &partida->jogador2;
				break;
		}
		if (jogadorAtual->tipo == 1)
		tecladoJoga(jogadorAtual);
	else if (jogadorAtual->tipo == 2)
		iaJoga(jogadorAtual);

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

void rodarPartidaRemota(t_partidaRemota *partida);

void iniciaRemoto() {
	t_partidaRemota partida;

	configuraTabuleiro(&partida.tabuleiro);

	configuraJogadoresRemotos(&partida.jogador, &partida.tabuleiro);

	conecta(&partida.jogador);

	rodarPartidaRemota(&partida);
}

void rodarPartidaRemota(t_partidaRemota *partida) {
	for (partida->rodada = 1; partida->rodada <= 9; ++partida->rodada) {
		desenha(&partida->tabuleiro);
		printf("Você é o %c.\n", partida->jogador.caractere);

		// Host joga nos pares
		if (partida->jogador.ehHost) {
			switch(partida->rodada % 2) {
				case 0:
					remotoJoga(&partida->jogador);
					break;
				case 1:
					printf("Vez do adversário.\n");
					recebeJogada(&partida->jogador);
					break;
			}
		}

		// Client joga nos ímpares
		else {
			switch(partida->rodada % 2) {
				case 1:
					remotoJoga(&partida->jogador);
					break;
				case 0:
					printf("Vez do adversário.\n");
					recebeJogada(&partida->jogador);
					break;
			}
		}

		// Verifica se alguém ganhou
		if (partida->rodada >= 5) {
			partida->vencedor = temVencedor(&partida->tabuleiro);

			if (partida->vencedor) {
				break;
			}
		}
	}

	desenha(&partida->tabuleiro);

	// Encerra conexão
	close(partida->jogador.cliente_fd);
	if (partida->jogador.ehHost)
		close(partida->jogador.servidor_fd);

	// Printa o vencedor
	if (partida->vencedor == partida->jogador.valor)
		puts("Você venceu.");
	else if (partida->vencedor == 0)
		puts("Deu velha.");
	else
		puts("Seu adversário venceu.");
}