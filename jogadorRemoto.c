#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "t_jogador.h"
#include "configRemoto.h"
#include "tabuleiro.h"

void configuraJogadoresRemotos(t_jogadorRemoto *jogador, t_tabuleiro *tabuleiro) {
	jogador->copiaTabuleiro = tabuleiro;

    jogador->valor = 0;

	// Configura se vai ser jogador x jogador, jogador x IA ou por socket.
	int escolhaTipo;
	printf("Digite 1 para hostear o jogo e 2 para se conectar a outro jogo: ");
	while (jogador->valor == 0) {
		scanf("%d", &escolhaTipo);
		switch (escolhaTipo) {
			case 1:
				jogador->ehHost = 1;
                jogador->valor = 1;
                jogador->caractere = 'O';
				break;
			case 2:
				jogador->ehHost = 0;
                jogador->valor = 4;
                jogador->caractere = 'X';
				break;
			default:
				printf("\nO valor digitado não é válido. Tente novamente: ");
				break;
		}
	}

    jogador->cliente_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (jogador->cliente_fd < 0) {
        perror("Erro ao criar socket do cliente.");
        exit(EXIT_FAILURE);
    }

    if (jogador->ehHost) {
	    jogador->servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (jogador->servidor_fd < 0) {
            perror("Erro ao criar socket do servidor.");
            exit(EXIT_FAILURE);
        }
    }
}

void enviaJogada(t_jogadorRemoto *jogador, int x, int y, int valor);

void remotoJoga(t_jogadorRemoto *jogador) {
    int x, y;
	printf("Digite as coordenadas em que deseja jogar no seguinte formato: \"x,y\": ");
	while (1) {
		scanf("%d,%d", &x, &y);

		// Se a jogada for possível.
		if (verificarJogada(jogador->copiaTabuleiro, x - 1, y - 1)) {
			marcaJogada(jogador->copiaTabuleiro, x - 1, y - 1, jogador->valor);
            enviaJogada(jogador, x - 1, y - 1, jogador->valor);
			break;
		}
		// Se a jogada não for possível.
		else {
			printf("Essa posição não é válida. Digite novamente: ");
		}
	}
}

void conecta(t_jogadorRemoto *jogador) {
    if (jogador->ehHost) {
        struct sockaddr_in endereco;
        socklen_t endereco_len = sizeof(endereco);

        endereco.sin_family = AF_INET;
        endereco.sin_addr.s_addr = INADDR_ANY;
        endereco.sin_port = htons(PORTA);

        // Associa socket à porta
        if (bind(jogador->servidor_fd, (struct sockaddr *)&endereco, sizeof(endereco)) < 0) {
            perror("Erro no bind");
            close(jogador->servidor_fd);
            exit(EXIT_FAILURE);
        }

        // Escuta conexões
        if (listen(jogador->servidor_fd, 1) < 0) {
            perror("Erro no listen");
            close(jogador->servidor_fd);
            exit(EXIT_FAILURE);
        }

        printf("Servidor aguardando conexao na porta %d...\n", PORTA);

        jogador->cliente_fd = accept(jogador->servidor_fd, (struct sockaddr *)&endereco, &endereco_len);
        if (jogador->cliente_fd < 0) {
            perror("Erro no accept");
            close(jogador->servidor_fd);
            exit(EXIT_FAILURE);
        }
    }

    else {
        struct sockaddr_in servidor;

        jogador->cliente_fd = socket(AF_INET, SOCK_STREAM, 0);

        if (jogador->cliente_fd < 0) {
            perror("Erro ao criar socket");
            exit(EXIT_FAILURE);
        }

        servidor.sin_family = AF_INET;
        servidor.sin_port = htons(PORTA);

        if (inet_pton(AF_INET, "127.0.0.1", &servidor.sin_addr) <= 0) {
            perror("Endereco invalido");
            close(jogador->cliente_fd);
            exit(EXIT_FAILURE);
        }

        if (connect(jogador->cliente_fd, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
            perror("Erro ao conectar");
            close(jogador->cliente_fd);
            exit(EXIT_FAILURE);
        }
    }
}

void enviaJogada(t_jogadorRemoto *jogador, int x, int y, int valor) {
    // É determinado por "x y v", x e y são as coordenadas, e v é o valor
    jogador->buffer[0] = x + '0';
    jogador->buffer[1] = ' ';
    jogador->buffer[2] = y + '0';
    jogador->buffer[3] = ' ';
    jogador->buffer[4] = valor + '0';
    jogador->buffer[5] = '\0';

    send(jogador->cliente_fd, jogador->buffer, strlen(jogador->buffer) + 1, 0);
}

// Jogador recebe algo do tipo "1 1 4" e interpreta
void recebeJogada(t_jogadorRemoto *jogador) {
    memset(jogador->buffer, 0, TAM_BUFFER);
    int bytes = recv(jogador->cliente_fd, jogador->buffer, TAM_BUFFER, 0);

    if (bytes <= 0) {
            printf("O outro usuário se desconectou.\n");

            close(jogador->cliente_fd);
            if (jogador->ehHost)
                close(jogador->servidor_fd);
    }

    int x, y, valor;
    // É determinado por "x y v", x e y são as coordenadas, e v é o valor
    x = jogador->buffer[0] - '0';
    y = jogador->buffer[2] - '0';
    valor = jogador->buffer[4] - '0';
    marcaJogada(jogador->copiaTabuleiro, x, y, valor);
}