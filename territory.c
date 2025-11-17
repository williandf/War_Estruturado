#include "territory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *strdup_safe(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *p = (char*)malloc(len + 1);
    if (!p) { fprintf(stderr, "Erro: malloc nome/cor\n"); exit(1); }
    memcpy(p, s, len + 1);
    return p;
}

Territory *territories_create(int n) {
    Territory *v = (Territory*)calloc(n, sizeof(Territory));
    if (!v) { fprintf(stderr, "Erro: calloc territories\n"); exit(1); }
    for (int i = 0; i < n; ++i) {
        v[i].id = i;
        v[i].ownerId = -1;
        v[i].troops = 0;
        v[i].neighbors = NULL;
        v[i].degree = 0;
        v[i].cap = 0;
    }
    return v;
}

void territory_set(Territory *t, int id, const char *name, const char *color, int ownerId, int troops) {
    t->id = id;
    t->name = strdup_safe(name);
    t->color = strdup_safe(color);
    t->ownerId = ownerId;
    t->troops = troops;
}

void territories_print(const Territory *v, int n) {
    printf("=== Estado dos Territorios ===\n");
    for (int i = 0; i < n; ++i) {
        printf("#%d %-16s cor=%-8s owner=%d tropas=%d vizinhos=",
               v[i].id, v[i].name ? v[i].name : "(null)",
               v[i].color ? v[i].color : "(null)",
               v[i].ownerId, v[i].troops);
        for (size_t j = 0; j < v[i].degree; ++j) {
            printf("%d%s", v[i].neighbors[j], (j+1<v[i].degree)?",":"");
        }
        printf("\n");
    }
    printf("==============================\n");
}

void territory_add_neighbor(Territory *t, int neighborId) {
    if (t->degree == t->cap) {
        size_t newcap = t->cap ? t->cap * 2 : 4;
        int *nv = (int*)realloc(t->neighbors, newcap * sizeof(int));
        if (!nv) { fprintf(stderr, "Erro: realloc neighbors\n"); exit(1); }
        t->neighbors = nv;
        t->cap = newcap;
    }
    t->neighbors[t->degree++] = neighborId;
}

int territory_are_adjacent(const Territory *v, int n, int a, int b) {
    if (a < 0 || a >= n || b < 0 || b >= n) return 0;
    for (size_t i = 0; i < v[a].degree; ++i) {
        if (v[a].neighbors[i] == b) return 1;
    }
    return 0;
}

void territories_destroy(Territory *v, int n) {
    if (!v) return;
    for (int i = 0; i < n; ++i) {
        free(v[i].name);
        free(v[i].color);
        free(v[i].neighbors);
        v[i].name = NULL;
        v[i].color = NULL;
        v[i].neighbors = NULL;
    }
    free(v);
}