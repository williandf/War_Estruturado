#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "territory.h"
#include "attack.h"
#include "mission.h"

// Cria um mapa pequeno (6 territorios) e dois jogadores (0 e 1)
static int setup_sample_map(Territory **out, Mission ***outMissions) {
    int n = 6;
    Territory *v = territories_create(n);

    // América do Sul (0,1,2) / Ásia (3,4,5) - apenas exemplo simbólico
    territory_set(&v[0], 0, "Brasil",        "verde",  0, 4);
    territory_set(&v[1], 1, "Argentina",     "azul",   0, 3);
    territory_set(&v[2], 2, "Chile",         "vermelho", 0, 3);

    territory_set(&v[3], 3, "China",         "amarelo", 1, 4);
    territory_set(&v[4], 4, "India",         "roxo",    1, 3);
    territory_set(&v[5], 5, "Russia",        "cinza",   1, 3);

    // vizinhanças (bidirecionais)
    territory_add_neighbor(&v[0], 1); territory_add_neighbor(&v[1], 0);
    territory_add_neighbor(&v[1], 2); territory_add_neighbor(&v[2], 1);
    territory_add_neighbor(&v[0], 2); territory_add_neighbor(&v[2], 0); // triângulo AS

    territory_add_neighbor(&v[3], 4); territory_add_neighbor(&v[4], 3);
    territory_add_neighbor(&v[4], 5); territory_add_neighbor(&v[5], 4);
    territory_add_neighbor(&v[3], 5); territory_add_neighbor(&v[5], 3); // triângulo Ásia

    // ponte intercontinental simples (Brasil - China)
    territory_add_neighbor(&v[0], 3); territory_add_neighbor(&v[3], 0);

    // Missão: controlar 4 territorios para vencer (para ambos os jogadores)
    Mission **missions = (Mission**)calloc(2, sizeof(Mission*));
    missions[0] = mission_create_controlN(4);
    missions[1] = mission_create_controlN(4);

    *out = v;
    *outMissions = missions;
    return n;
}

static void destroy_all(Territory *v, int n, Mission **missions) {
    mission_destroy(missions[0]);
    mission_destroy(missions[1]);
    free(missions);
    territories_destroy(v, n);
}

int main(void) {
    srand((unsigned)time(NULL));

    Territory *v = NULL;
    Mission **missions = NULL;
    int n = setup_sample_map(&v, &missions);

    int currentPlayer = 0;
    int running = 1;

    printf("WAR Estruturado - Exemplo de CLI\n");
    printf("Jogadores: 0 e 1. Missao: controlar 4 territorios.\n");
    printf("Comandos: \n");
    printf("  1 - Mostrar mapa\n");
    printf("  2 - Atacar (from to)\n");
    printf("  3 - Mover tropas (from to qty)\n");
    printf(" -1 - Sair\n\n");

    while (running) {
        printf("Vez do jogador %d > ", currentPlayer);
        int cmd;
        if (scanf("%d", &cmd) != 1) { break; }

        if (cmd == -1) {
            break;
        } else if (cmd == 1) {
            territories_print(v, n);
        } else if (cmd == 2) {
            int a, b;
            printf("Atacar de (id) para (id): ");
            if (scanf("%d %d", &a, &b) != 2) { printf("Entrada invalida.\n"); continue; }
            if (a < 0 || a >= n || b < 0 || b >= n) { printf("Ids invalidos.\n"); continue; }
            if (v[a].ownerId != currentPlayer) { printf("Territorio de origem nao pertence ao jogador.\n"); continue; }
            int lostA=0, lostD=0;
            int conquered = attack_resolve(v, n, a, b, &lostA, &lostD);
            (void)conquered;
            printf("Perdas: atacante -%d, defensor -%d\n", lostA, lostD);
            // checa vitoria
            if (missions[currentPlayer]->check(missions[currentPlayer], v, n, currentPlayer)) {
                printf("Jogador %d venceu sua missao! Fim de jogo.\n", currentPlayer);
                break;
            }
            // alterna turno apenas apos um comando de ataque/movimento
            currentPlayer = 1 - currentPlayer;
        } else if (cmd == 3) {
            int a, b, q;
            printf("Mover tropas: from to qty: ");
            if (scanf("%d %d %d", &a, &b, &q) != 3) { printf("Entrada invalida.\n"); continue; }
            if (a < 0 || a >= n || b < 0 || b >= n) { printf("Ids invalidos.\n"); continue; }
            if (v[a].ownerId != currentPlayer || v[b].ownerId != currentPlayer) {
                printf("So pode mover entre seus proprios territorios.\n"); continue; }
            move_troops(v, n, a, b, q);
            // checa vitoria
            if (missions[currentPlayer]->check(missions[currentPlayer], v, n, currentPlayer)) {
                printf("Jogador %d venceu sua missao! Fim de jogo.\n", currentPlayer);
                break;
            }
            currentPlayer = 1 - currentPlayer;
        } else {
            printf("Comando desconhecido.\n");
        }
    }

    destroy_all(v, n, missions);
    printf("Encerrado.\n");
    return 0;
}