//
// Created by ASUS on 2/1/2026.
//

#ifndef ADS_BASICS_GRAPH_H
#define ADS_BASICS_GRAPH_H
#include <stddef.h>

typedef struct edge_s { // Renamed tag for consistency
    int dest;
    int weight;
    struct edge_s* next;
} edge_t;

typedef struct {
    int nv; // Number of vertices
    edge_t** adjList;
} graph_t;

graph_t* create_graph(int num_vertices);
void destroy_graph(graph_t* g);

void add_edge(graph_t* g, int u, int v, int weight);
void remove_edge(graph_t* g, int u, int v);
void clear_edges(graph_t* g);


int has_edge(const graph_t* g, int u, int v);
void print_neighbors(const graph_t* g, int u);

#endif //ADS_BASICS_GRAPH_H