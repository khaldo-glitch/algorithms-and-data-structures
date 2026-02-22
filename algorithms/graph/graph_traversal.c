#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "graph_algorithms.h"

/**
 * BFS - Computes shortest paths from start node s.
 * Returns a pointer to a BFSResult struct, or NULL on failure.
 */
BFSResult* BFS(graph_t* g, int s) {

    if (g == NULL || s < 0 || s >= g->nv) {
        return NULL;
    }

    BFSResult* res = malloc(sizeof(BFSResult));
    if (!res) {
        fprintf(stderr,"Memory allocation failed\n");
        return NULL;
    }

    res->dist = malloc(g->nv * sizeof(int));
    res->pred = malloc(g->nv * sizeof(int));
    int* color = malloc(g->nv * sizeof(int));

    if (res->dist ==NULL || res->pred ==NULL || color==NULL) {
        fprintf(stderr,"Memory allocation failed\n");
        free(color);
        free(res->dist);
        free(res->pred);
        free(res);
        return NULL;
    }


    for (int v = 0; v < g->nv; v++) {
        color[v] = WHITE;
        res->dist[v] = -1;
        res->pred[v] = -1;
    }

    queue_t* q = queue_create();
    if (!q) {
        free(color);
        free(res->dist);
        free(res->pred);
        free(res);
        return NULL;
    }

    color[s] = GRAY;
    res->dist[s] = 0;
    queue_enqueue(q, s);



    while (!queue_is_empty(q)) {
        qnode_t* temp = queue_dequeue(q);
        int u = temp->data;
        free(temp);

        for (edge_t* e = g->adjList[u]; e != NULL; e = e->next) {
            int v = e->dest;
            if (color[v] == WHITE) {
                color[v] = GRAY;
                res->dist[v] = res->dist[u] + 1;
                res->pred[v] = u;
                queue_enqueue(q, v);
            }
        }
        color[u] = BLACK;
    }

    free(color);
    queue_destroy(q);

    return res;
}