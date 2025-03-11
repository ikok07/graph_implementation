//
// Created by Kok on 3/11/25.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "lib/include/hash_table.h"

typedef struct edge {
    hash_table_item_t *dest;
} graph_edge_t;

typedef struct graph_node {
    void *value;
    size_t value_size;
    graph_edge_t **edges;
    size_t edge_count;
    int visited;
} graph_node_t;

typedef struct graph {
    hash_table_t *nodes;
} graph_t;


graph_t *graph_create(int size);
void graph_destroy(graph_t *graph);

void graph_node_destroy(graph_node_t *node);
void graph_edge_destroy(graph_edge_t *edge);

graph_node_t *graph_node_search(graph_t *graph, char *node_id);
graph_t *graph_node_insert(graph_t *graph, char *node_id, void *value, size_t value_size);
graph_t *graph_node_remove(graph_t *graph, char *node_id);

graph_t *graph_edge_insert(graph_t *graph, int node_id, int dest_node_id);
graph_t *graph_edge_remove(graph_t *graph, int node_id, int dest_node_id);

// TODO: Implement BFS algorithm

#endif //GRAPH_H
