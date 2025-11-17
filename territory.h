#ifndef TERRITORY_H
#define TERRITORY_H

#include <stddef.h>

// Estrutura base do jogo (vetor de structs) + vizinhança (grafo simples).
typedef struct Territory {
    int id;             // índice 0..n-1
    char *name;         // alocado dinamicamente
    char *color;        // alocado dinamicamente
    int ownerId;        // -1 = sem dono
    int troops;         // quantidade de tropas
    int *neighbors;     // ids dos vizinhos (lista dinâmica)
    size_t degree;      // quantidade de vizinhos
    size_t cap;         // capacidade do vetor neighbors
} Territory;

// --- Criação / destruição ---
Territory *territories_create(int n);
void territories_destroy(Territory *v, int n);

// --- Cadastro básico ---
void territory_set(Territory *t, int id, const char *name, const char *color, int ownerId, int troops);
void territories_print(const Territory *v, int n);

// --- Vizinhança (grafo simples) ---
void territory_add_neighbor(Territory *t, int neighborId);
int  territory_are_adjacent(const Territory *v, int n, int a, int b);

#endif