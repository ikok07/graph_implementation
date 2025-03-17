//
// Created by Kok on 3/9/25.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *id;
    void *value;
    size_t value_size;
    bool should_free;
} linked_list_item_t;

typedef struct linked_list {
    linked_list_item_t *item;
    struct linked_list *next;
} linked_list_t;

linked_list_t *list_allocate();
linked_list_item_t *list_read(linked_list_t *list, char *item_id);
linked_list_t *list_insert(linked_list_t *list, linked_list_item_t *item);
linked_list_t *list_remove(linked_list_t *list, char *item_id);
linked_list_t *list_remove_from_edge(linked_list_t *list, int from_start);

linked_list_item_t *list_item_create(char *id, void *value, size_t value_size, bool should_free);

void list_node_free(linked_list_t *list);

#endif //LINKED_LIST_H
