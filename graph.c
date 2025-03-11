//
// Created by Kok on 3/11/25.
//

#include "graph.h"

#include <string.h>

graph_t *graph_create(const int size) {
    graph_t *graph = malloc(sizeof(graph_t));
    if (!graph) return NULL;

    graph->nodes = hash_table_create(size);

    return graph;
}

graph_node_t *graph_node_create(void *value, size_t value_size, graph_edge_t **edges, size_t edge_count) {
    if (value == NULL) return NULL;

    graph_node_t *node = malloc(sizeof(graph_node_t));
    if (node == NULL) return NULL;

    node->value_size = value_size;
    node->edge_count = edge_count;
    node->value = malloc(value_size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    if (edges != NULL && edge_count > 0) {
        node->edges = malloc(sizeof(graph_edge_t) * edge_count);
        if (node->edges == NULL) {
            free(node->value);
            free(node);
            return NULL;
        }
        memcpy(node->edges, edges, sizeof(graph_edge_t) * edge_count);
    }

    memcpy(node->value, value, value_size);
    return node;
}

graph_edge_t *graph_edge_create(hash_table_item_t *hash_node_item) {
    if (hash_node_item == NULL) return NULL;

    graph_edge_t *edge = malloc(sizeof(graph_edge_t));
    if (edge == NULL) return NULL;

    edge->dest = hash_node_item;

    return edge;
}

graph_node_t *graph_node_search(graph_t *graph, char *node_id) {
    if (graph == NULL || graph->nodes == NULL) return NULL;

    hash_table_item_t *found_hash_node = hash_table_search(graph->nodes, node_id);
    if (found_hash_node == NULL) return NULL;

    graph_node_t *found_node = (graph_node_t*)found_hash_node->value;
    return found_node;
}

graph_t *graph_node_insert(graph_t *graph, hash_table_item_t *node) {
    if (graph == NULL || node == NULL || node->key == NULL) return NULL;

    graph_node_t *new_graph_node = (graph_node_t*)node->value;
    if (new_graph_node == NULL) return NULL;

    hash_table_item_t *found_hash_node_item = hash_table_search(graph->nodes, node->key);
    if (found_hash_node_item != NULL) {
        graph_node_t *found_node = (graph_node_t*)found_hash_node_item->value;

        if (found_node != NULL) {
            void *temp = malloc(new_graph_node->value_size);
            if (temp == NULL) return NULL;
            memcpy(temp, new_graph_node->value, new_graph_node->value_size);

            free(found_node->value);
            found_node->value = temp;
            found_node->value_size = new_graph_node->value_size;

            return graph;
        }
    }

    if (hash_table_insert(graph->nodes, node) != 0) return NULL;
    return graph;
}

graph_t *graph_node_remove(graph_t *graph, char *node_id) {
    if (graph == NULL || graph->nodes == NULL) return NULL;

    hash_table_item_t *hash_node = hash_table_search(graph->nodes, node_id);
    if (hash_node == NULL || hash_node->value == NULL) return NULL;

    graph_node_destroy(hash_node->value);

    if (hash_table_delete(graph->nodes, node_id) != 0) return NULL;
    return graph;
}

void graph_edge_destroy(graph_edge_t *edge) {
    if (edge == NULL) return;
    free(edge);
}

void graph_node_destroy(const graph_node_t *node) {
    if (node == NULL) return;

    if (node->value != NULL) free(node->value);
    for (int i = 0; i < node->edge_count; i++) {
        if (node->edges[i] != NULL) graph_edge_destroy(node->edges[i]);
        free(node->edges);
    }
}

void graph_destroy(graph_t *graph) {
    if (graph == NULL) return;
    if (graph->nodes != NULL) {
        for (int i = 0; i < graph->nodes->count; i++) {
            hash_table_item_t *item = hash_table_search(graph->nodes, );

            if (item != NULL) {
                if (item->value != NULL) {
                    graph_node_destroy(graph->nodes->items[i]->value);
                }
                hash_table_free_item(item);
            }
        }
    }
    free(graph);
}
