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

graph_node_t *graph_node_create(void *value, size_t value_size, graph_edge_t **edges, size_t edge_count);
void graph_node_destroy(const graph_node_t *node);

graph_edge_t *graph_edge_create(hash_table_item_t *hash_node_item);
void graph_edge_destroy(graph_edge_t *edge);

graph_node_t *graph_node_search(graph_t *graph, char *node_id);
graph_t *graph_node_insert(graph_t *graph, hash_table_item_t *node);
graph_t *graph_node_remove(graph_t *graph, char *node_id);

// TODO: Implement BFS algorithm
hash_table_item_t *graph_node_bfs_search(graph_t *graph, char *start_node_id, char *target_node_id);

#endif //GRAPH_H
