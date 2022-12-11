#include <stdlib.h>
#include <stdio.h>

#define NV 128

typedef struct aresta
{
    int dest;
    int custo;
    struct aresta *prox;
} * LAdj, *GrafoL[NV];

typedef int GrafoM[NV][NV];