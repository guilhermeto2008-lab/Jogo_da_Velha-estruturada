#include <stdio.h>
#include "partida.h"

int main() {
    char decisaoJogador = decidirTipoPartida();
    printf("\033[2J\033[H");
    if (decisaoJogador == 'L')
        iniciaLocal();
    else if (decisaoJogador == 'R')
        iniciaRemoto();
 
    return 0;
}