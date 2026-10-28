#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct {
	/*
		Tipos:
	1 = jogador real
	2 = IA
	3 = Socket
	*/
	int tipo;
	int valor;
	char caractere;
} t_jogador;

void configuraTiposJogadores(t_jogador *jogador1, t_jogador *jogador2);
void configuraCaracteresJogadores(t_jogador *jogador1, t_jogador *jogador2);
void joga(t_jogador jogador);

#endif
