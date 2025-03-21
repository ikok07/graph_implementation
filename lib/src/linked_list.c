//
// Created by Kok on 3/9/25.
//

#include <stdlib.h>

#include "../include/linked_list.h"

#include <string.h>

linked_list_t *list_allocate() {
    linked_list_t *list = malloc(sizeof(linked_list_t));
    return list;
}

linked_list_item_t *list_read(linked_list_t *list, char *item_id) {
    if (list == NULL) return NULL;

    linked_list_t *curr_node = list;

    while (curr_node != NULL) {
        if (curr_node->item != NULL && strcmp(curr_node->item->id, item_id) == 0) return curr_node->item;
        curr_node = curr_node->next;
    }

    return NULL;
}

linked_list_t *list_insert(linked_list_t *list, linked_list_item_t *item) {
    linked_list_t *new_node = list_allocate();
    if (new_node == NULL) return NULL;

    new_node->item = item;
    new_node->next = list;

    return new_node;
}

linked_list_t *list_remove(linked_list_t *list, char *item_id) {
    if (list == NULL) return NULL;

    linked_list_t *prev_node = NULL;
    linked_list_t *curr_node = list;

    while (curr_node != NULL) {
        if (curr_node->item && strcmp(curr_node->item->id, item_id) == 0) {
            if (prev_node == NULL) list = curr_node->next;
            else prev_node->next = curr_node->next;
            list_node_free(curr_node);
            return list;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    return list;
}

linked_list_t *list_remove_from_edge(linked_list_t *list, int from_start) {
    if (list == NULL) return NULL;

    if (from_start) {
        linked_list_t *next_node = list->next;
        list_node_free(list);

        return next_node;
    }

    linked_list_t *prev_node = NULL;
    linked_list_t *curr_node = list;

    while (curr_node->next != NULL) {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    list_node_free(curr_node);
    return prev_node;
}

linked_list_item_t *list_item_create(char *id, void *value, size_t value_size, bool should_free) {
    linked_list_item_t *list_item = malloc(sizeof(linked_list_item_t));
    if (list_item == NULL) return NULL;

    list_item->value_size = value_size;
    list_item->should_free = should_free;

    list_item->id = malloc(strlen(id) + 1);
    if (list_item->id == NULL) {
        free(list_item);
        return NULL;
    }
    memcpy(list_item->id, id, strlen(id) + 1);

    list_item->value = malloc(value_size);
    if (list_item->value == NULL) {
        free(list_item->id);
        free(list_item);
        return NULL;
    }
    memcpy(list_item->value, value, value_size);

    return list_item;
}

void list_node_free(linked_list_t *node) {
    if (node == NULL) return;

    if (node->item != NULL && node->item->should_free) {
        if (node->item->id != NULL) free(node->item->id);
        if (node->item->value != NULL) free(node->item->value);
        free(node->item);
    }

    free(node);
}
