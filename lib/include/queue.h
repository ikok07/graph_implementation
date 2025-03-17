//
// Created by Kok on 3/16/25.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <linked_list.h>
#include <stdlib.h>

typedef struct {
    linked_list_t *items;
    size_t value_size;
    size_t count;
    size_t size;
} queue_t;

queue_t *queue_create(size_t size, size_t value_size);
void queue_destroy(queue_t *queue);

int queue_insert(queue_t *queue, void *value);
void *queue_pop(queue_t *queue);

#endif //QUEUE_H
