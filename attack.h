#ifndef ATTACK_H
#define ATTACK_H

#include "territory.h"

// Resolve um ataque único de fromId -> toId.
// Retorna 1 se o defensor foi conquistado, 0 caso contrário.
// lostAtt/lostDef são perdas retornadas por referência.
int attack_resolve(Territory *v, int n, int fromId, int toId, int *lostAtt, int *lostDef);

void move_troops(Territory *v, int n, int fromId, int toId, int qty);

#endif