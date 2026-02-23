#ifndef ADS_BASICS_GRAPH_ALGORITHMS_H
#define ADS_BASICS_GRAPH_ALGORITHMS_H

#include "graph.h"
// ============================================================
// Graph Traversal
// ============================================================

enum {WHITE, GRAY, BLACK};

typedef struct {
    int* dist;
    int* pred;
} BFSResult;

BFSResult* BFS(graph_t* g, int s);

// ============================================================
// Single-Source Shortest Path (SSSP)
// ============================================================

BFSResult* dijkstra(graph_t* g, int sourceNode);
int* shortestPath(graph_t* g, int source, int target, int* minCost, int* pathLength);

// ============================================================
// Minimum Spanning Tree (MST)
// ============================================================

// Represents an edge in the final MST result
typedef struct {
    int u, v, weight;
} mst_edge_t;

// The result of an MST algorithm
typedef struct {
    mst_edge_t* edges;
    int num_edges;
    int total_weight;
} MSTResult;

MSTResult* prim_mst(graph_t* g, int start_node);

MSTResult* kruskal_mst(graph_t* g);


#endif //ADS_BASICS_GRAPH_ALGORITHMS_H