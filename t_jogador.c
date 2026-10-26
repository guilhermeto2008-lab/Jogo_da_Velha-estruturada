#include <stdio.h>
#include "t_jogador.h"
#include "jogadorTeclado.h"
#include "jogadorIA.h"

void joga(t_jogador jogador) {
	if (jogador.tipo == 1)
		tecladoJoga(jogador);
	else if (jogador.tipo == 2)
		iaJoga(jogador);
}

