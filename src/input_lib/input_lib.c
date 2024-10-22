#include "input_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input_str(char *str) {
    size_t current_size = INPUT_DEFAULT_SIZE;

    char *buffer = (char *)malloc(current_size * sizeof(char));

    if (buffer != NULL) {
        size_t length = 0;
        while (fgets(buffer + length, current_size - length, stdin) != NULL) {
            length += strcspn(buffer + length, "\n");
            if (buffer[length] == '\n') {
                buffer[length] = '\0';
                break;
            }

            current_size = (size_t)(current_size * 1.5);
            char *new_buffer = realloc(buffer, current_size);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
        }

        free(str);
    }

    return buffer;
}

int input_digit(int *digit) {
    int is_valid = 1;
    char input[INPUT_DEFAULT_SIZE];
    char *end;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        is_valid = 0;
    }

    if (is_valid) {
        input[strcspn(input, "\n")] = '\0';
        *digit = strtol(input, &end, 10);

        if (*end != '\0') {
            is_valid = 0;
        }
    }

    return is_valid;
}
