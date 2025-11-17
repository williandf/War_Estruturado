#ifndef MISSION_H
#define MISSION_H

#include "territory.h"

typedef enum { MISSION_CONTROL_N = 0 } MissionType;

typedef struct Mission {
    MissionType type;
    int paramA; // N territorios
    int (*check)(struct Mission *m, Territory *v, int n, int playerId);
} Mission;

Mission *mission_create_controlN(int n);
void mission_destroy(Mission *m);

#endif