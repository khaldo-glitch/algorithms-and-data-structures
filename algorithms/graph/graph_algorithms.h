//
// Created by ASUS on 2/1/2026.
//

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

/**
 * @brief Finds the MST using Prim's algorithm.
 * @param g The graph.
 * @param start_node The node to start building the MST from.
 * @return A pointer to an MSTResult struct. Caller must free the struct and its 'edges' array.
 */
MSTResult* prim_mst(graph_t* g, int start_node);

/**
 * @brief Finds the MST using Kruskal's algorithm.
 * @param g The graph.
 * @return A pointer to an MSTResult struct. Caller must free the struct and its 'edges' array.
 */
MSTResult* kruskal_mst(graph_t* g);


#endif //ADS_BASICS_GRAPH_ALGORITHMS_H