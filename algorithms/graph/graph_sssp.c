#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph_algorithms.h"

int minGray(BFSResult* res, int colors [] ,int n) {
    int minDist= INT_MAX;
    int node=-1;
    for (int i=0;i<n;i++) {
        if (colors[i]==GRAY && res->dist[i] < minDist) {
            minDist = res->dist[i];
            node=i;
        }
    }
    return node;
}

// ---------------------------------------------
// WORKER FUNCTION: performs Dijkstra
// No allocation, no freeing.
// Only updates res->dist and res->pred.
// ---------------------------------------------
static void dijkstra_visit(graph_t* g, int source, int* color, BFSResult* res) {
    // Initialization done by the wrapper
    res->dist[source] = 0;
    color[source] = GRAY;

    for (int i = 0; i < g->nv; i++) {
        int u = minGray(res, color, g->nv);
        if (u == -1)
            break;

        color[u] = BLACK;

        // Relax edges
        for (edge_t* e = g->adjList[u]; e != NULL; e = e->next) {
            int v = e->dest;
            int w = e->weight;

            if (res->dist[u] != INT_MAX && res->dist[v] > res->dist[u] + w) {
                if (color[v] == WHITE)
                    color[v] = GRAY;

                res->dist[v] = res->dist[u] + w;
                res->pred[v] = u;
            }
        }
    }
}
// ---------------------------------------------
// WRAPPER FUNCTION: allocates memory,
// initializes tables, calls the worker,
// and returns the result.
// ---------------------------------------------
BFSResult* dijkstra(graph_t* g, int sourceNode) {

    BFSResult* res = malloc(sizeof(BFSResult));
    res->dist = malloc(g->nv * sizeof(int));
    res->pred = malloc(g->nv * sizeof(int));
    int* color = malloc(g->nv * sizeof(int));

    // Initialize everything
    for (int i = 0; i < g->nv; i++) {
        color[i] = WHITE;
        res->dist[i] = INT_MAX;
        res->pred[i] = -1;
    }

    // Call worker
    dijkstra_visit(g, sourceNode, color, res);

    free(color);
    return res;
}


int* shortestPath(graph_t* g, int source, int target, int* minCost, int* pathLength) {
    BFSResult* res = dijkstra(g, source);

    if (res->dist[target] == INT_MAX) {
        printf("Path cannot be done, nodes are disconnected\n");
        free(res->dist);
        free(res->pred);
        free(res);
        return NULL;
    }

    // Temporary array to build the path backwards
    int* temp = malloc(g->nv * sizeof(int));
    int count = 0;

    int node = target;
    while (node != -1) {
        temp[count++] = node;
        if (node == source)
            break;
        node = res->pred[node];
    }

    *pathLength = count;
    *minCost = res->dist[target];



    int* path = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        path[i] = temp[count - 1 - i];
    }
    free(temp);
    free(res->dist);
    free(res->pred);
    free(res);

    return path;
}
