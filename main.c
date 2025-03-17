#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "queue.h"

#define GRAPH_SIZE          100

int main(void) {

    graph_t *graph = graph_create(GRAPH_SIZE);

    graph_node_t *n2 = graph_node_create((char*)"World", strlen("World") + 1, NULL, 0);
    if (n2 == NULL) return -1;

    hash_table_item_t *n2_hash_item = hash_table_item_create("N2", n2, sizeof(graph_node_t*));
    if (n2_hash_item == NULL) return -1;

    graph_edge_t *e1 = graph_edge_create(n2_hash_item);
    if (e1 == NULL) return -1;

    graph_node_t *n1 = graph_node_create((char*)"Hello", strlen("Hello") + 1, &e1, 1);
    if (n1 == NULL) return -1;

    hash_table_item_t *n1_hash_item = hash_table_item_create("N1", n1, sizeof(graph_node_t*));
    if (n1_hash_item == NULL) return -1;

    graph = graph_node_insert(graph, n1_hash_item);
    graph = graph_node_insert(graph, n2_hash_item);

    // graph = graph_node_remove(graph, "N1");
    // graph_node_t *found_node = graph_node_search(graph, "N1");
    hash_table_item_t *found_node = graph_node_bfs_search(graph, "N1", "N2");
    printf("%s", (char*)((graph_node_t*)found_node->value)->value);

    graph_destroy(graph);

    return 0;
}
