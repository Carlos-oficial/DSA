#include "graph.h"

int DF(GrafoL g, int or,
       int v[],
       int p[],
       int l[])
{
    int i;
    for (i = 0; i < NV; i++)
    {
        v[i] = 0;
        p[i] = -1;
        l[i] = -1;
    }
    p[or] = -1;
    l[or] = 0;
    return DFRec(g, or, v, p, l);
}
int DFRec(GrafoL g, int or,
          int v[],
          int p[],
          int l[])
{
    int i;
    LAdj a;
    i = 1;
    v[or] = -1;
    for (a = g[or];
         a != NULL;
         a = a->prox)
        if (!v[a->dest])
        {
            p[a->dest] = or ;
            l[a->dest] = 1 + l[or];
            i += DFRec(g, a->dest, v, p, l);
        }
    v[or] = 1;
    return i;
}

int BF(GrafoL g, int or,
       int v[],
       int p[],
       int l[])
{
    int i, x;
    LAdj a;
    int q[NV], front, end;
    for (i = 0; i < NV; i++)
    {
        v[i] = 0;
        p[i] = -1;
        l[i] = -1;
    }
    front = end = 0;
    q[end++] = or ; // enqueue
    v[or] = 1;
    p[or] = -1;
    l[or] = 0;
    i = 1;
    while (front != end)
    {
        x = q[front++]; // dequeue
        for (a = g[x]; a != NULL; a = a->prox)
            if (!v[a->dest])
            {
                i++;
                v[a->dest] = 1;
                p[a->dest] = x;
                l[a->dest] = 1 + l[x];
                q[end++] = a->dest; // enqueue
            }
    }
    return i;
}