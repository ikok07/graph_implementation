//
// Created by Kok on 3/17/25.
//

#include "../include/utils.h"

#include <stdlib.h>
#include <time.h>

char random_char(int index) {
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    return charset[index];
}

char *random_string() {
    srand(time(NULL));
    char *str = malloc(sizeof(char) * 17);
    int i;

    for (i = 0; i < 16; i++) {
        str[i] = random_char(rand() % 62);
    }
    str[i] = '\0';
    return str;
}
