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

int auxiliarRegra1(t_jogador *jogador, int valorARevisar) {
	int i, j, somaLinha, somaColuna, linhaParaMarcar=-1, colunaParaMarcar=-1;

	// Verifica linhas e colunas que estão com duas marcações
	for (i = 0; i < 3; ++i) {
		// Se encontrou uma linha/coluna, sai da verificação e vai marcar ela
		if (linhaParaMarcar != -1 || colunaParaMarcar != -1)
			break;

		somaLinha = 0;
		somaColuna = 0;
		for (j = 0; j < 3; ++j) {
			somaLinha += acessarTabuleiro(jogador->copiaTabuleiro, i, j);
			somaColuna += acessarTabuleiro(jogador->copiaTabuleiro, j, i);
		}

		if (somaLinha == valorARevisar * 2)
			linhaParaMarcar = i;
		if (somaColuna == valorARevisar * 2)
			colunaParaMarcar = i;
	}

	// Se achou uma linha que já tem duas marcações
	if (linhaParaMarcar != -1) {
		for (j = 0; j < 3; ++j) {
			if (verificarJogada(jogador->copiaTabuleiro, linhaParaMarcar, j)) {
				marcaJogada(jogador->copiaTabuleiro, linhaParaMarcar, j, jogador->valor);
				return 1;
			}
		}
	}

	// Se achou uma coluna que já tem duas marcações
	if (colunaParaMarcar != -1) {
		for (i = 0; i < 3; ++i) {
			if (verificarJogada(jogador->copiaTabuleiro, i, colunaParaMarcar)) {
				marcaJogada(jogador->copiaTabuleiro, i, colunaParaMarcar, jogador->valor);
				return 1;
			}
		}
	}

	int somaDiagonalPrincipal=0, somaDiagonalSecundaria=0;

	// Verifica se alguém vai bater na diagonal principal
	j = 0;
	for (i = 0; i < 3; ++i) {
		somaDiagonalPrincipal += acessarTabuleiro(jogador->copiaTabuleiro, i, j);
		++j;
	}
	// Se alguém for bater na diagonal principal, marca esse espaço
	if (somaDiagonalPrincipal == valorARevisar * 2) {
		j = 0;
		for (i = 0; i < 3; ++i) {
			if (verificarJogada(jogador->copiaTabuleiro, i, j)) {
				marcaJogada(jogador->copiaTabuleiro, i, j, jogador->valor);
				return 1;
			}
		++j;
		}
	}

	j = 2;
	for (i = 0; i < 3; ++i) {
		somaDiagonalSecundaria += acessarTabuleiro(jogador->copiaTabuleiro, i, j);
		--j;
	}
	// Se alguém for bater na diagonal principal, marca esse espaço
	if (somaDiagonalSecundaria == valorARevisar * 2) {
		j = 2;
		for (i = 0; i < 3; ++i) {
			if (verificarJogada(jogador->copiaTabuleiro, i, j)) {
				marcaJogada(jogador->copiaTabuleiro, i, j, jogador->valor);
				return 1;
			}
		--j;
		}
	}

	return 0;
}

// Regras retornam 1 caso tenham marcado, e zero caso não tenham achado uma jogada correta.
int verificaRegra1(t_jogador *jogador) {
	int adversario;

	switch (jogador->valor) {
		case 1:
			adversario = 4;
			break;
		case 4:
			adversario = 1;
			break;
	}

	if (auxiliarRegra1(jogador, jogador->valor))
		return 1;
	else if (auxiliarRegra1(jogador, adversario))
		return 1;

	return 0;
}

int verificaRegra2(t_jogador *jogador) {
	int i, j;
	int somaLinha, somaColuna;
	int possivelLinha=-1, possivelColuna=-1;

	for (i = 0; i < 3; ++i) {
		// Enquanto não tiver achado uma possível linha ou possível coluna, continua procurando
		if (possivelLinha == -1 || possivelColuna == -1) {
			somaLinha = 0;
			somaColuna = 0;
			for (j = 0; j < 3; ++j) {
				somaLinha += acessarTabuleiro(jogador->copiaTabuleiro, i, j);
				somaColuna += acessarTabuleiro(jogador->copiaTabuleiro, j, i);
			}

			// Encontrou uma linha onde apenas ele possui uma marcação
			if (somaLinha == jogador->valor && possivelLinha == -1)
				possivelLinha = i;
			// Encontrou uma coluna onde apenas ele possui uma marcação
			if (somaColuna == jogador->valor && possivelColuna == -1)
				possivelColuna = i;
		}
	}

	// Se achou uma linha e coluna onde apenas ele tenha uma marcação, marca a posição que fecha o jogo para o adversário
	if (possivelLinha != -1 && possivelColuna != -1 && verificarJogada(jogador->copiaTabuleiro, possivelLinha, possivelColuna)) {
		marcaJogada(jogador->copiaTabuleiro, possivelLinha, possivelColuna, jogador->valor);
		return 1;
	}

	int somaDiagonalPrincipal = 0, somaDiagonalSecundaria = 0;

	int jPrimario = 0, jSecundario = 2;
	for (i = 0; i < 3; ++i) {
		somaDiagonalPrincipal += acessarTabuleiro(jogador->copiaTabuleiro, i, jPrimario);
		somaDiagonalSecundaria += acessarTabuleiro(jogador->copiaTabuleiro, i, jSecundario);

		++jPrimario;
		--jSecundario;
	}

	// Se a diagonal principal só estiver marcada pela IA
	if (somaDiagonalPrincipal == jogador->valor) {
		// Se tiver achado uma linha que ele fecha
		if (possivelLinha != -1 && verificarJogada(jogador->copiaTabuleiro, possivelLinha, possivelLinha)) {
			marcaJogada(jogador->copiaTabuleiro, possivelLinha, possivelLinha, jogador->valor);
			return 1;
		}
		if (possivelColuna != -1 && verificarJogada(jogador->copiaTabuleiro, possivelColuna, possivelColuna)) {
			marcaJogada(jogador->copiaTabuleiro, possivelColuna, possivelColuna, jogador->valor);
			return 1;
		}
	}

	// Se a diagonal secundária só tiver uma marcação da IA
	if (somaDiagonalSecundaria == jogador->valor) {
		// Lembre-se que a fórmula das posições que pertencem à diagonal secundária é dado por x + y = dim(matriz). Nesse caso, x + y = 2
		if (possivelLinha != -1 && verificarJogada(jogador->copiaTabuleiro, possivelLinha, 2 - possivelLinha)) {
			marcaJogada(jogador->copiaTabuleiro, possivelLinha, 2 - possivelLinha, jogador->valor);
			return 1;
		}
		if (possivelColuna != -1 && verificarJogada(jogador->copiaTabuleiro, 2 - possivelColuna, possivelColuna)) {
			marcaJogada(jogador->copiaTabuleiro, 2 - possivelColuna, possivelColuna, jogador->valor);
			return 1;
		}
	}

	return 0;
}

int verificaRegra3(t_jogador *jogador) {
	// Espaço central está vazio
	if (verificarJogada(jogador->copiaTabuleiro, 1, 1)) {
		marcaJogada(jogador->copiaTabuleiro, 1, 1, jogador->valor);
		return 1;
	}

	return 0;
}

int verificaRegra4(t_jogador *jogador) {
	int valorCanto;

	// 1,1 foi marcado, mas 3,3 não
	valorCanto = acessarTabuleiro(jogador->copiaTabuleiro, 0, 0);
	if (valorCanto != 0 && valorCanto != jogador->valor && verificarJogada(jogador->copiaTabuleiro, 2, 2)) {
		marcaJogada(jogador->copiaTabuleiro, 2, 2, jogador->valor);
		return 1;
	}
	// 1,3 foi marcado, mas 3,1 não
	valorCanto = acessarTabuleiro(jogador->copiaTabuleiro, 0, 2);
	if (valorCanto != 0 && valorCanto != jogador->valor && verificarJogada(jogador->copiaTabuleiro, 2, 0)) {
		marcaJogada(jogador->copiaTabuleiro, 2, 0, jogador->valor);
		return 1;
	}
	// 3,1 foi marcado, mas 1,3 não
	valorCanto = acessarTabuleiro(jogador->copiaTabuleiro, 2, 0);
	if (valorCanto != 0 && valorCanto !=jogador->valor && verificarJogada(jogador->copiaTabuleiro, 0, 2)) {
		marcaJogada(jogador->copiaTabuleiro, 0, 2, jogador->valor);
		return 1;
	}
	// 3,3 foi marcado, mas 1,1 não
	valorCanto = acessarTabuleiro(jogador->copiaTabuleiro, 2, 2);
	if (valorCanto != 0 && valorCanto != jogador->valor && verificarJogada(jogador->copiaTabuleiro, 0, 0)) {
		marcaJogada(jogador->copiaTabuleiro, 0, 0, jogador->valor);
		return 1;
	}

	// Não existe esse caso
	return 0;
}

int verificaRegra5(t_jogador *jogador) {
	if (verificarJogada(jogador->copiaTabuleiro, 0, 0)) {
		marcaJogada(jogador->copiaTabuleiro, 0, 0, jogador->valor);
		return 1;
	}
	if (verificarJogada(jogador->copiaTabuleiro, 0, 2)) {
		marcaJogada(jogador->copiaTabuleiro, 0, 2, jogador->valor);
		return 1;
	}
	if (verificarJogada(jogador->copiaTabuleiro, 2, 0)) {
		marcaJogada(jogador->copiaTabuleiro, 2, 0, jogador->valor);
		return 1;
	}
	if (verificarJogada(jogador->copiaTabuleiro, 2, 2)) {
		marcaJogada(jogador->copiaTabuleiro, 2, 2, jogador->valor);
		return 1;
	}

	// Não encontrou canto vazio
	return 0;
}

void verificaRegra6(t_jogador *jogador) {
	int i, j;

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (verificarJogada(jogador->copiaTabuleiro, i, j)) {
				marcaJogada(jogador->copiaTabuleiro, i, j, jogador->valor);
				return;
			}
		}
	}
}

void iaJoga(t_jogador *jogador) {
	// Verifica cada uma da regras. Se uma encontrou um ligar para marcar, retorna 1. Se não, retorna 0 e segue para a próxima regra.
	if (verificaRegra1(jogador) || verificaRegra2(jogador) || verificaRegra3(jogador) || verificaRegra4(jogador) || verificaRegra5(jogador))
		return;
	verificaRegra6(jogador);
}