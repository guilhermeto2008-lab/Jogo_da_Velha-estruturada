#include <stdio.h>

typedef struct {
	short int M[3][3];
} t_tabuleiro;
static t_tabuleiro tabuleiro;

// Zera o tabuleiro por completo
void limparTabuleiro() {
	int i, j;                                                                                                                                                                                 
    for (i = 0; i < 3; ++i) {                                                                                                                                                                 
        for (j = 0; j < 3; ++j) {                                                                                                                                                             
            tabuleiro.M[i][j] = 0;
        }                                                                                                                                                                                     
    }	
}

// Verifica se é possível jogar na posição desejada pelo jogador
int verificarJogada(short int x, short int y) {
	if (x < 0 || x > 2 || y < 0 || y > 2)
		return 0;
	if (tabuleiro.M[x][y] != 0)
		return 0;
	return 1;
}

void desenha() {
	printf("\033[2J\033[H");
	int i, j;
	char caractere;

	for (i = 0; i < 3; ++i) {
		printf(" ");
		for (j = 0; j < 3; ++j) {
			// Traduz de valores para caracteres X e O
			if (tabuleiro.M[i][j] == 0)
				caractere = ' ';
			else if (tabuleiro.M[i][j] == 1)
				caractere = 'O';
			else
				caractere = 'X';

			// Printa os valores da linha
			if (j != 2)
				printf("%c | ", caractere);
			else 
				printf("%c\n", caractere);
		}

		// Printa a divisão de linhas
		if (i != 2)
			puts("———————————");
	}
}

// Retorna 0 para não tem, 1 para X e 2 para O
int temVencedor() {
	short int somaLinhas = 0, somaColunas = 0;

	short int i, j;

	// Verificação de linhas e colunas
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			somaLinhas += tabuleiro.M[i][j];
			somaColunas += tabuleiro.M[j][i];

			// Se for a última soma de linha/coluna verifica se tem vencedor daquela linha/coluna
			if (j == 2) {
				if (somaLinhas == 3 || somaColunas == 3)
					return 1;
				if (somaLinhas == 12 || somaColunas == 12)
					return 4;
				somaLinhas = 0;
				somaColunas = 0;
			}
		}
	}

	// Verificação das diagonais
	short int somaDiagonalPrincipal = 0, somaDiagonalSecundaria = 0;
	short int x, yPrincipal = 0, ySecundaria = 2;

	for (x = 0; x < 3; ++x) {
		somaDiagonalPrincipal += tabuleiro.M[x][yPrincipal];
		somaDiagonalSecundaria += tabuleiro.M[x][ySecundaria];

		++yPrincipal;
		--ySecundaria;
	}

	if (somaDiagonalPrincipal == 3 || somaDiagonalSecundaria == 3)
		return 1;
	if (somaDiagonalPrincipal == 12 || somaDiagonalSecundaria == 12)
		return 4;

	return 0;
}

void marcaJogada(short int x, short int y, short int valor) {
	tabuleiro.M[x][y] = valor;
}
