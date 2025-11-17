#include "attack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int attack_resolve(Territory *v, int n, int fromId, int toId, int *lostAtt, int *lostDef) {
    if (!territory_are_adjacent(v, n, fromId, toId)) {
        printf("Nao sao vizinhos.\n");
        return 0;
    }
    Territory *A = &v[fromId];
    Territory *D = &v[toId];
    if (A->troops < 2) {
        printf("Atacante precisa de pelo menos 2 tropas.\n");
        return 0;
    }
    if (A->ownerId == D->ownerId) {
        printf("Nao pode atacar territorio do mesmo dono.\n");
        return 0;
    }

    // Rolagens simples com base no numero de tropas
    int atkRoll = (rand() % (A->troops - 1)) + 1;
    int defRoll = (rand() % (D->troops   > 0 ? D->troops : 1)) + 1;

    if (atkRoll > defRoll) {
        *lostAtt = 1; *lostDef = 2;
    } else {
        *lostAtt = 2; *lostDef = 1;
    }
    if (*lostAtt >= A->troops) *lostAtt = A->troops - 1; // sempre sobra 1
    if (*lostDef >= D->troops) *lostDef = D->troops;      // pode zerar

    A->troops -= *lostAtt;
    D->troops -= *lostDef;

    if (D->troops <= 0) {
        // conquista
        D->ownerId = A->ownerId;
        D->troops = 1;
        A->troops -= 1; // move 1 tropa minima
        printf("Territorio %d conquistado por jogador %d!\n", D->id, A->ownerId);
        return 1;
    }
    return 0;
}

void move_troops(Territory *v, int n, int fromId, int toId, int qty) {
    if (!territory_are_adjacent(v, n, fromId, toId)) {
        printf("Nao sao vizinhos.\n");
        return;
    }
    Territory *A = &v[fromId];
    Territory *B = &v[toId];
    if (A->ownerId != B->ownerId) {
        printf("Movimento apenas entre territorios do mesmo dono.\n");
        return;
    }
    if (qty <= 0 || qty >= A->troops) {
        printf("Quantidade invalida (deve sobrar ao menos 1).\n");
        return;
    }
    A->troops -= qty;
    B->troops += qty;
    printf("Movidas %d tropas de %d -> %d\n", qty, fromId, toId);
}