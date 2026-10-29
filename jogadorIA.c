/****
* Implementação do módulo: jogadorIA.c
* Autor: Caio Rodrigues Silva
* Data de Criação: 23/10/2026
* Última alteração: 28/10/2026
* Descrição Geral: Fornece toda a infraestrutura para decisão de jogadas da IA.
****/

#include <stdio.h>
#include "t_jogador.h"
#include "tabuleiro.h"

int auxiliarRegra1(int valorJogador, int valorARevisar) {
	int i, j, somaLinha, somaColuna, linhaParaMarcar=-1, colunaParaMarcar=-1;

	// Verifica linhas e colunas que estão com duas marcações
	for (i = 0; i < 3; ++i) {
		// Se encontrou uma linha/coluna, sai da verificação e vai marcar ela
		if (linhaParaMarcar != -1 || colunaParaMarcar != -1)
			break;

		somaLinha = 0;
		somaColuna = 0;
		for (j = 0; j < 3; ++j) {
			somaLinha += valorPosicao(i, j);
			somaColuna += valorPosicao(j, i);
		}

		if (somaLinha == valorARevisar * 2) {
			linhaParaMarcar = i;
			break;
		} else if (somaColuna == valorARevisar * 2) {
			colunaParaMarcar = i;
			break;
		}
	}

	// Se achou uma linha que já tem duas marcações
	if (linhaParaMarcar != -1) {
		for (j = 0; j < 3; ++j) {
			if (verificarJogada(linhaParaMarcar, j)) {
				marcaJogada(linhaParaMarcar, j, valorJogador);
				return 1;
			}
		}
	}

	// Se achou uma coluna que já tem duas marcações
	if (colunaParaMarcar != -1) {
		for (i = 0; i < 3; ++i) {
			if (verificarJogada(i, colunaParaMarcar)) {
				marcaJogada(i, colunaParaMarcar, valorJogador);
				return 1;
			}
		}
	}

	int somaDiagonalPrincipal=0, somaDiagonalSecundaria=0;

	// Verifica se alguém vai bater na diagonal principal
	j = 0;
	for (i = 0; i < 3; ++i) {
		somaDiagonalPrincipal += valorPosicao(i, j);
		++j;
	}
	// Se alguém for bater na diagonal principal, marca esse espaço
	if (somaDiagonalPrincipal == valorARevisar * 2) {
		j = 0;
		for (i = 0; i < 3; ++i) {
			if (verificarJogada(i, j)) {
				marcaJogada(i, j, valorJogador);
				return 1;
			}
		++j;
		}
	}

	j = 2;
	for (i = 0; i < 3; ++i) {
		somaDiagonalSecundaria += valorPosicao(i, j);
		--j;
	}
	// Se alguém for bater na diagonal principal, marca esse espaço
	if (somaDiagonalSecundaria == valorARevisar * 2) {
		j = 2;
		for (i = 0; i < 3; ++i) {
			if (verificarJogada(i, j)) {
				marcaJogada(i, j, valorJogador);
				return 1;
			}
		--j;
		}
	}

	return 0;
}

// Regras retornam 1 caso tenham marcado, e zero caso não tenham achado uma jogada correta.
int verificaRegra1(int valorJogador) {
	int adversario;

	switch (valorJogador) {
		case 1:
			adversario = 4;
			break;
		case 4:
			adversario = 1;
			break;
	}

	if (auxiliarRegra1(valorJogador, valorJogador))
		return 1;
	else if (auxiliarRegra1(valorJogador, adversario))
		return 1;

	return 0;
}

int verificaRegra2(int valorJogador) {
	int i, j;
	int somaLinha, somaColuna;
	int possivelLinha=-1, possivelColuna=-1;

	for (i = 0; i < 3; ++i) {
		// Enquanto não tiver achado uma possível linha ou possível coluna, continua procurando
		if (possivelLinha == -1 || possivelColuna == -1) {
			somaLinha = 0;
			somaColuna = 0;
			for (j = 0; j < 3; ++j) {
				somaLinha += valorPosicao(i, j);
				somaColuna += valorPosicao(j, i);
			}

			// Encontrou uma linha onde apenas ele possui uma marcação
			if (somaLinha == valorJogador && possivelLinha == -1)
				possivelLinha = i;
			// Encontrou uma coluna onde apenas ele possui uma marcação
			if (somaColuna == valorJogador && possivelColuna == -1)
				possivelColuna = i;
		}
	}

	// Se achou uma linha e coluna onde apenas ele tenha uma marcação, marca a posição que fecha o jogo para o adversário
	if (possivelLinha != -1 && possivelColuna != -1 && verificarJogada(possivelLinha, possivelColuna)) {
		marcaJogada(possivelLinha, possivelColuna, valorJogador);
		return 1;
	}

	int somaDiagonalPrincipal=0;

	j = 0;
	for (i = 0; i < 3; ++i) {
		somaDiagonalPrincipal += valorPosicao(i, j);
		++j;
	}

	// Se a diagonal principal só estiver marcada pela IA
	if (somaDiagonalPrincipal == valorJogador) {
		// Se tiver achado uma linha que ele fecha
		if (possivelLinha != -1 && verificarJogada(possivelLinha, possivelLinha)) {
			marcaJogada(possivelLinha, possivelLinha, valorJogador);
			return 1;
		}
		if (possivelColuna != -1 && verificarJogada(possivelColuna, possivelColuna)) {
			marcaJogada(possivelColuna, possivelColuna, valorJogador);
			return 1;
		}
	}

	int somaDiagonalSecundaria=0;

	j = 2;
	for (i = 0; i < 3; ++i) {
		somaDiagonalSecundaria += valorPosicao(i, j);
		--j;
	} 

	// Se a diagonal secundária só tiver uma marcação da IA
	if (somaDiagonalSecundaria == valorJogador) {
		// Lembre-se que a fórmula das posições que pertencem à diagonal secundária é dado por x + y = dim(matriz). Nesse caso, x + y = 2
		if (possivelLinha != -1 && verificarJogada(possivelLinha, 2 - possivelLinha)) {
			marcaJogada(possivelLinha, 2 - possivelLinha, valorJogador);
			return 1;
		}
		if (possivelColuna != -1 && verificarJogada(2 - possivelColuna, possivelColuna)) {
			marcaJogada(2 - possivelColuna, possivelColuna, valorJogador);
			return 1;
		}
	}

	return 0;
}

int verificaRegra3(int valorJogador) {
	// Espaço central está vazio
	if (verificarJogada(1, 1)) {
		marcaJogada(1, 1, valorJogador);
		return 1;
	}

	return 0;
}

int verificaRegra4(int valorJogador) {
	int valorCanto;

	// 1,1 foi marcado, mas 3,3 não
	valorCanto = valorPosicao(0, 0);
	if (valorCanto != 0 && valorCanto != valorJogador && verificarJogada(2, 2)) {
		marcaJogada(2, 2, valorJogador);
		return 1;
	}
	// 1,3 foi marcado, mas 3,1 não
	valorCanto = valorPosicao(0, 2);
	if (valorCanto != 0 && valorCanto != valorJogador && verificarJogada(2, 0)) {
		marcaJogada(2, 0, valorJogador);
		return 1;
	}
	// 3,1 foi marcado, mas 1,3 não
	valorCanto = valorPosicao(2, 0);
	if (valorCanto != 0 && valorCanto != valorJogador && verificarJogada(0, 2)) {
		marcaJogada(0, 2, valorJogador);
		return 1;
	}
	// 3,3 foi marcado, mas 1,1 não
	valorCanto = valorPosicao(2, 2);
	if (valorCanto != 0 && valorCanto != valorJogador && verificarJogada(0, 0)) {
		marcaJogada(0, 0, valorJogador);
		return 1;
	}

	// Não existe esse caso
	return 0;
}

int verificaRegra5(int valorJogador) {
	if (verificarJogada(0, 0)) {
		marcaJogada(0, 0, valorJogador);
		return 1;
	}
	if (verificarJogada(0, 2)) {
		marcaJogada(0, 2, valorJogador);
		return 1;
	}
	if (verificarJogada(2, 0)) {
		marcaJogada(2, 0, valorJogador);
		return 1;
	}
	if (verificarJogada(2, 2)) {
		marcaJogada(2, 2, valorJogador);
		return 1;
	}

	// Não encontrou canto vazio
	return 0;
}

void verificaRegra6(int valorJogador) {
	int i, j;

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (verificarJogada(i, j)) {
				marcaJogada(i, j, valorJogador);
				return;
			}
		}
	}
}

void iaJoga(t_jogador jogador) {
	// Verifica cada uma da regras. Se uma encontrou um ligar para marcar, retorna 1. Se não, retorna 0 e segue para a próxima regra.
	if (verificaRegra1(jogador.valor) || verificaRegra2(jogador.valor) || verificaRegra3(jogador.valor) || verificaRegra4(jogador.valor) || verificaRegra5(jogador.valor))
		return;
	verificaRegra6(jogador.valor);
}