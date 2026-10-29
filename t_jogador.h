#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct {
	int tipo;
	int valor;
	char caractere;
} t_jogador;

void configuraTiposJogadores(t_jogador *jogador1, t_jogador *jogador2);
void configuraCaracteresJogadores(t_jogador *jogador1, t_jogador *jogador2);
void joga(t_jogador jogador);

#endif
