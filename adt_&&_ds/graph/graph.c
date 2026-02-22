//
// Created by ASUS on 2/1/2026.
//

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

graph_t* create_graph(int num_vertices) {
    graph_t* g = malloc(sizeof(graph_t));
    if (g == NULL) {
        fprintf(stderr, "Memory allocation failed for graph struct\n");
        return NULL;
    }
    g->nv = num_vertices;

    g->adjList = malloc(num_vertices * sizeof(edge_t*));
    if (g->adjList == NULL) {
        fprintf(stderr, "Memory allocation failed for adjacency list\n");
        free(g);
        return NULL;
    }

    for (int i = 0; i < num_vertices; i++) {
        g->adjList[i] = NULL;
    }

    return g;
}

void destroy_graph(graph_t* g) {
    if (g == NULL) return;
    clear_edges(g); // Use clear_edges to free all edge nodes
    free(g->adjList); // Free the array of pointers
    free(g);          // Free the graph struct itself
}

void add_edge(graph_t* g, int u, int v, int weight) {
    if (g == NULL || u < 0 || u >= g->nv || v < 0 || v >= g->nv) return;

    edge_t* new_edge = malloc(sizeof(edge_t));
    if (new_edge == NULL) {
        fprintf(stderr, "Memory allocation failed for new edge\n");
        return;
    }
    new_edge->dest = v;
    new_edge->weight = weight;
    new_edge->next = g->adjList[u];
    g->adjList[u] = new_edge;
}

void remove_edge(graph_t* g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->nv) return;

    edge_t* curr = g->adjList[u];
    edge_t* prev = NULL;

    while (curr != NULL) {
        if (curr->dest == v) {
            if (prev == NULL) {
                g->adjList[u] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void clear_edges(graph_t* g) {
    if (g == NULL) return;
    for (int i = 0; i < g->nv; i++) {
        edge_t* curr = g->adjList[i];
        while (curr != NULL) {
            edge_t* temp = curr;
            curr = curr->next;
            free(temp);
        }
        g->adjList[i] = NULL;
    }
}

int has_edge(const graph_t* g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->nv) return 0;

    const edge_t* e;
    for (e = g->adjList[u]; e != NULL; e = e->next) {
        if (e->dest == v) return 1;
    }
    return 0;
}

void print_neighbors(const graph_t* g, int u) {
    if (g == NULL || u < 0 || u >= g->nv) return;

    const edge_t* e;
    printf("Neighbors of %d: ", u);
    for (e = g->adjList[u]; e != NULL; e = e->next) {
        printf("%d(w:%d) ", e->dest, e->weight);
    }
    printf("\n");
}
