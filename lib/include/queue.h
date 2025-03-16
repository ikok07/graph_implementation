//
// Created by Kok on 3/16/25.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct {
    void **items;
    int tail_index;
    size_t value_size;
    size_t size;
} queue_t;

queue_t *queue_create(size_t size, size_t value_size);
void queue_destroy(queue_t *queue);

int queue_insert(queue_t *queue, const void *value);
void *queue_pop(queue_t *queue);

#endif //QUEUE_H
