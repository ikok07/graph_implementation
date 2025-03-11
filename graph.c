//
// Created by Kok on 3/11/25.
//

#include "graph.h"

#include <secure/_string.h>

graph_t *graph_create(const int size) {
    graph_t *graph = malloc(sizeof(graph_t));
    if (!graph) return NULL;

    graph->nodes = hash_table_create(size);

    return graph;
}

void graph_edge_destroy(graph_edge_t *edge) {
    if (edge == NULL) return;
    free(edge);
}

graph_node_t *graph_node_search(graph_t *graph, char *node_id) {
    if (graph == NULL || graph->nodes == NULL) return NULL;

    graph_node_t *found_node = (graph_node_t*)hash_table_search(graph->nodes, node_id);
    return found_node;
}

graph_t *graph_node_insert(graph_t *graph, char *node_id, void *value, size_t value_size) {
    if (graph == NULL) return NULL;

    graph_node_t *found_node = (graph_node_t*)hash_table_search(graph->nodes, node_id);

    if (found_node != NULL) {
        void *temp = malloc(value_size);
        if (temp == NULL) return NULL;
        memcpy(temp, value, value_size);

        free(found_node->value);
        found_node->value = temp;
        found_node->value_size = value_size;

        return graph;
    }

    hash_table_item_t *new_node = hash_table_item_create(node_id, value, value_size);
    if (new_node == NULL) return NULL;

    if (hash_table_insert(graph->nodes, new_node) != 0) {
        hash_table_free_item(new_node);
        return NULL;
    }
    return graph;
}

graph_t *graph_node_remove(graph_t *graph, char *node_id) {
    if (graph == NULL || graph->nodes == NULL) return NULL;

    if (hash_table_delete(graph->nodes, node_id) != 0) return NULL;
    return graph;
}

void graph_node_destroy(graph_node_t *node) {
    if (node == NULL) return;

    if (node->value != NULL) free(node->value);
    for (int i = 0; i < node->edge_count; i++) {
        if (node->edges[i] != NULL) graph_edge_destroy(node->edges[i]);
        free(node->edges);
    }

    free(node);
}

void graph_destroy(graph_t *graph) {
    if (graph == NULL) return;
    if (graph->nodes != NULL) {
        for (int i = 0; i < graph->nodes->count; i++) {
            hash_table_item_t *item = graph->nodes->items[i];

            if (item != NULL) {
                if (item->value != NULL) {
                    graph_node_destroy(graph->nodes->items[i]->value);
                }
                hash_table_free_item(item);
            }
        }
    }

    hash_table_free(graph->nodes);
    free(graph);
}
