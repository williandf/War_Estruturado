# War Estruturado (C)

Projeto-base para o desafio **War Estruturado** em C.

Atende aos três itens do enunciado:
1. Cadastro de territórios usando **vetor de structs** (`Territory`).
2. **Ataque entre territórios** usando **ponteiros** e **alocação dinâmica**.
3. **Missões estratégicas** com **ponteiro para função** para verificar condição de vitória.

## Estrutura
- `src/main.c`
- `src/territory.c` / `src/territory.h`
- `src/attack.c` / `src/attack.h`
- `src/mission.c` / `src/mission.h`
- `Makefile`

## Como compilar
```bash
make
```

## Como executar
```bash
./war
```

## Controles no terminal
- `1` → mostrar mapa
- `2` → atacar (informe `fromId toId`)
- `3` → mover tropas (informe `fromId toId qty`)
- `-1` → sair

Missão padrão: **controlar 4 territórios**. Mapa de exemplo com 6 territórios e 2 jogadores (0 e 1).

## Memória
- Strings (`name`, `color`) alocadas com `malloc` e liberadas em `territories_destroy`.
- Vizinhança (`neighbors`) alocada dinamicamente com `realloc` por território.
- Missões alocadas com `malloc` e liberadas em `destroy_all`.