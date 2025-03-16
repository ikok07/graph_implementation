//
// Created by Kok on 3/16/25.
//

#include "queue.h"

#include <stdio.h>
#include <string.h>

queue_t *queue_create(const size_t size, const size_t value_size) {
    queue_t *queue = malloc(sizeof(queue_t));
    queue->value_size = value_size;
    queue->size = size;
    queue->tail_index = 0;
    queue->items = malloc(sizeof(void*) * queue->size);
    if (queue->items == NULL) {
        free(queue);
        return NULL;
    }

    for (int i = 0; i < queue->size; i++) {
        queue->items[i] = NULL;
    }

    return queue;
}

void queue_destroy(queue_t *queue) {
    for (int i = 0; i < queue->size; i++) {
        free(queue->items[i]);
    }

    free(queue->items);
    free(queue);
}

int queue_insert(queue_t *queue, const void *value) {
    if (queue == NULL) return -1;

    if (queue->tail_index >= queue->size) {
        perror("Queue is full!");
        return -1;
    }

    queue->items[queue->tail_index] = malloc(queue->value_size);
    if (queue->items[queue->tail_index] == NULL) {
        perror("Could not allocate space for item in the queue!");
        return -1;
    }

    memcpy(queue->items[queue->tail_index], value, queue->value_size);

    queue->tail_index++;
    return 0;
}

void *queue_pop(queue_t *queue) {
    if (queue == NULL || queue->tail_index == 0) return NULL;

    void *return_value = malloc(queue->value_size);
    if (return_value == NULL) return NULL;
    memcpy(return_value, queue->items[0], queue->value_size);
    free(queue->items[0]);

    for (int i = 1; i < queue->tail_index; i++) {
        queue->items[i - 1] = queue->items[i];
    }
    queue->items[queue->tail_index - 1] = NULL;

    queue->tail_index--;

    return return_value;
}
