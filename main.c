#include <stdio.h>
#include "partida.h"

int main() {
    char decisaoJogador = decidirTipoPartida();
    if (decisaoJogador == 'L')
        iniciaLocal();
    else if (decisaoJogador == 'R')
        iniciaRemoto();
 
    return 0;
}