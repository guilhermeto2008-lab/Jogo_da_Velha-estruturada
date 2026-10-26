#ifndef JOGADOR_H
#define JOGADOR_H

/*
	Tipos:
1 = jogador real
2 = IA
3 = Socket
*/
typedef struct {
	int tipo;
	int valor;
	char caractere;
} t_jogador;

void joga(t_jogador jogador);

#endif
