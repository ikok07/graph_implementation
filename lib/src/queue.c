//
// Created by Kok on 3/16/25.
//

#include "../include/queue.h"

#include <stdio.h>
#include <string.h>

#include "utils.h"

queue_t *queue_create(const size_t size, const size_t value_size) {
    queue_t *queue = malloc(sizeof(queue_t));
    queue->value_size = value_size;
    queue->size = size;
    queue->count = 0;
    queue->items = NULL;

    return queue;
}

void queue_destroy(queue_t *queue) {
    if (queue == NULL) return;
    if (queue->items == NULL) {
        free(queue);
        return;
    }

    linked_list_t *list_node = queue->items;
    while (list_node != NULL) {
        linked_list_t *temp_node = list_node->next;
        list_node_free(list_node);
        list_node = temp_node;
    }

    free(queue);
}

int queue_insert(queue_t *queue, void *value) {
    if (queue == NULL) return -1;

    if (queue->count >= queue->size) {
        perror("Queue is full!");
        return -1;
    }

    linked_list_item_t *list_item = list_item_create(random_string(), value, queue->value_size, true);
    if (list_item == NULL) return -1;

    queue->items = list_insert(queue->items, list_item);
    queue->count++;

    return 0;
}

void *queue_pop(queue_t *queue) {
    if (queue == NULL || queue->count == 0) return NULL;

    void *return_value = malloc(queue->value_size);
    if (return_value == NULL) return NULL;
    memcpy(return_value, queue->items->item->value, queue->value_size);

    queue->items = list_remove_from_edge(queue->items, true);
    queue->count--;

    return return_value;
}
