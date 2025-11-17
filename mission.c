#include "mission.h"
#include <stdlib.h>

static int check_controlN(Mission *m, Territory *v, int n, int playerId) {
    int total = 0;
    for (int i = 0; i < n; ++i) if (v[i].ownerId == playerId) total++;
    return total >= m->paramA;
}

Mission *mission_create_controlN(int n) {
    Mission *m = (Mission*)malloc(sizeof(Mission));
    if (!m) return NULL;
    m->type = MISSION_CONTROL_N;
    m->paramA = n;
    m->check = check_controlN;
    return m;
}

void mission_destroy(Mission *m) {
    free(m);
}