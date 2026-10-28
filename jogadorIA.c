#include <stdio.h>
#include <stdlib.h>
#include "t_jogador.h"
#include "tabuleiro.h"

// Regras retornam 1 caso tenham marcado, e zero caso não tenham achado uma jogada correta.
int verificaRegra1(int valorJogador, int matriz[3][3]) {
	int i, j, somaLinha, somaColuna, linhaParaMarcar=-1, colunaParaMarcar=-1;

	// Verifica linhas e colunas que estão com duas marcações
	for (i = 0; i < 3; ++i) {
		// Se encontrou uma linha/coluna, sai da verificação e vai marcar ela
		if (linhaParaMarcar != -1 || colunaParaMarcar != -1)
			break;

		somaLinha = 0;
		somaColuna = 0;
		for (j = 0; j < 3; ++j) {
			somaLinha += matriz[i][j];
			somaColuna += matriz[j][i];
		}

		if (somaLinha == 2 || somaLinha == 8) {
			linhaParaMarcar = i;
			break;
		} else if (somaColuna == 2 || somaColuna == 8) {
			colunaParaMarcar = i;
			break;
		}
	}

	// Se achou uma linha que já tem duas marcações
	if (linhaParaMarcar != -1) {
		for (colunaParaMarcar = 0; colunaParaMarcar < 3; ++colunaParaMarcar) {
			if (matriz[linhaParaMarcar][colunaParaMarcar] == 0) {
				marcaJogada(linhaParaMarcar, colunaParaMarcar, valorJogador);
				return 1;
			}
		}
	}

	// Se achou uma coluna que já tem duas marcações
	if (colunaParaMarcar != -1) {
		for (linhaParaMarcar = 0; linhaParaMarcar < 3; ++linhaParaMarcar) {
			if (matriz[linhaParaMarcar][colunaParaMarcar] == 0) {
				marcaJogada(linhaParaMarcar, colunaParaMarcar, valorJogador);
				return 1;
			}
		}
	}

	int somaDiagonalPrincipal, somaDiagonalSecundaria;

	// Verifica se alguém vai bater na diagonal principal
	j = 0;
	for (i = 0; i < 3; ++i) {
		somaDiagonalPrincipal += matriz[i][j];
		++j;
	}
	// Se alguém for bater na diagonal principal, marca esse espaço
	if (somaDiagonalPrincipal == 2 || somaDiagonalPrincipal == 8) {
		j = 0;
		for (i = 0; i < 3; ++i) {
			if (matriz[i][j] == 0) {
				marcaJogada(i, j, valorJogador);
				return 1;

			++j;
			}
		}
	}
	

	//Verifica se alguém vai bater na diagonal secundária
	j = 2;
	for (i = 0; i < 3; ++i) {
		somaDiagonalSecundaria += matriz[i][j];
		--j;
	}
	// Se alguém for bater na diagonal secundária, marca esse espaço
	if (somaDiagonalSecundaria == 2 || somaDiagonalSecundaria == 8) {
		j = 2;
		for (i = 0; i < 3; ++i) {
			if (matriz[i][j] == 0) {
				marcaJogada(i, j, valorJogador);
				return 1;
			}

			--j;
		}
	}

	// Não achou nenhum caso válido para marcar
	return 0;
}

int verificaRegra2(int valorJogador, int matriz[3][3]) {
	int i, j;
	int somaLinha, somaColuna;
	int possivelLinha=-1, possivelColuna=-1;

	for (i = 0; i < 3; ++i) {
		// Enquanto não tiver achado uma possível linha ou possível coluna, continua procurando
		if (possivelLinha == -1 || possivelColuna == -1) {
			somaLinha = 0;
			somaColuna = 0;
			for (j = 0; j < 3; ++j) {
				somaLinha += matriz[i][j];
				somaColuna += matriz[j][i];
			}

			// Encontrou uma linha onde apenas ele possui uma marcação
			if (somaLinha == valorJogador && possivelLinha != -1)
				possivelLinha = i;
			// Encontrou uma coluna onde apenas ele possui uma marcação
			if (somaColuna == valorJogador && possivelColuna != -1)
				possivelColuna = i;
		}
	}

	// Se achou uma linha e coluna onde apenas ele tenha uma marcação, marca a posição que fecha o jogo para o adversário
	if (possivelLinha != -1 && possivelColuna != -1) {
		marcaJogada(possivelLinha, possivelColuna, valorJogador);
		return 1;
	}

	int somaDiagonalPrincipal=0;

	j = 0;
	for (i = 0; i < 3; ++i) {
		somaDiagonalPrincipal += matriz[i][j];
		++j;
	}

	// Se a diagonal principal só estiver marcada pela IA
	if (somaDiagonalPrincipal == valorJogador) {
		// Se tiver achado uma linha que ele fecha
		if (possivelLinha != -1) {
			marcaJogada(possivelLinha, possivelLinha, valorJogador);
			return 1;
		}
		if (possivelColuna != -1) {
			marcaJogada(possivelColuna, possivelColuna, valorJogador);
			return 1;
		}
	}

	int somaDiagonalSecundaria=0;

	j = 2;
	for (i = 0; i < 3; ++i) {
		somaDiagonalSecundaria += matriz[i][j];
		--j;
	} 

	// Se a diagonal secundária só tiver uma marcação da IA
	if (somaDiagonalSecundaria == valorJogador) {
		// Lembre-se que a fórmula das posições que pertencem à diagonal secundária é dado por x + y = dim(matriz). Nesse caso, x + y = 2
		if (possivelLinha != -1) {
			marcaJogada(possivelLinha, 2 - possivelLinha, valorJogador);
			return 1;
		}
		if (possivelColuna != -1) {
			marcaJogada(2 - possivelColuna, possivelColuna, valorJogador);
			return 1;
		}
	}

	return 0;
}

int verificaRegra3(int valorJogador, int matriz[3][3]) {
	// Espaço central está vazio
	if (matriz[1][1] == 0) {
		marcaJogada(1, 1, valorJogador);
		return 1;
	}

	return 0;
}

int verificaRegra4(int valorJogador, int matriz[3][3]) {
	// 1,1 foi marcado, mas 3,3 não
	if (matriz[0][0] != 0 && matriz[0][0] != valorJogador && matriz[2][2] == 0) {
		marcaJogada(2, 2, valorJogador);
		return 1;
	}
	// 3,3 foi marcado, mas 1,1 não
	if (matriz[2][2] != 0 && matriz[2][2] != valorJogador && matriz[0][0] == 0) {
		marcaJogada(0, 0, valorJogador);
		return 1;
	}
	// 1,3 foi marcado, mas 3,1 não
	if (matriz[0][2] != 0 && matriz[0][2] != valorJogador && matriz[2][0] == 0) {
		marcaJogada(2, 0, valorJogador);
		return 1;
	}
	// 3,1 foi marcado, mas 1,3 não
	if (matriz[2][0] != 0 && matriz[2][0] != valorJogador && matriz[0][2] == 0) {
		marcaJogada(0, 2, valorJogador);
		return 1;
	}

	// Não existe esse caso
	return 0;
}

int verificaRegra5(int valorJogador, int matriz[3][3]) {
	if (matriz[0][0] == 0) {
		marcaJogada(0, 0, valorJogador);
		return 1;
	}
	if (matriz[0][2] == 0) {
		marcaJogada(0, 2, valorJogador);
		return 1;
	}
	if (matriz[2][0] == 0) {
		marcaJogada(0, 2, valorJogador);
		return 1;
	}
	if (matriz[2][2] == 0) {
		marcaJogada(0, 2, valorJogador);
		return 1;
	}

	// Não encontrou canto vazio
	return 0;
}

void verificaRegra6(int valorJogador, int matriz[3][3]) {
	int i, j;

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (matriz[i][j] == 0) {
				marcaJogada(i, j, valorJogador);
				return;
			}
		}
	}
}

void iaJoga(t_jogador jogador) {
	t_tabuleiro tabuleiro = acessarTabuleiro();

	// Verifica cada uma da regras. Se uma encontrou um ligar para marcar, retorna 1. Se não, retorna 0 e segue para a próxima regra.
	if (verificaRegra1(jogador.valor, tabuleiro.M) || verificaRegra2(jogador.valor, tabuleiro.M) || verificaRegra3(jogador.valor, tabuleiro.M) || verificaRegra4(jogador.valor, tabuleiro.M) || verificaRegra5(jogador.valor, tabuleiro.M))
		return;
	verificaRegra6(jogador.valor, tabuleiro.M);
}
