#include "input_lib.h"

#include <stdio.h>
#include <stdlib.h>

char *scan_input_characters(char *array, const int *size) {
    if (array != NULL) {
        int used_size = 0;
        int allocated_size = *size;
        char *cur = array;

        while (scanf("%c", cur) == 1 && *cur != '\n' && *cur != EOF) {
            used_size++;
            cur++;

            if (allocated_size - 1 < used_size) {
                allocated_size *= 2;

                char *new_array = (char *)realloc(array, allocated_size * sizeof(char));

                if (new_array == NULL) {
                    break;
                }

                array = new_array;
                cur = new_array + used_size;
            }
        }

        *cur = '\0';
    } else {
        fprintf(stderr, "Error: Initial array is NULL.\n");
    }

    return array;
}

char *input_sting(int default_size) {
    char *input_array = NULL;

    if (default_size > 1) {
        default_size++;

        input_array = (char *)calloc(default_size, sizeof(char));

        if (input_array != NULL) {
            input_array = scan_input_characters(input_array, &default_size);
        }
    }

    return input_array;
}

int input_single_digit(int *digit) {
    int end;

    int is_valid = (scanf("%d%c", digit, (char *)&end) == 2 && end == '\n') ? 1 : 0;

    if (!is_valid) {
        while ((end = getchar()) != '\n' && end != EOF);
    }

    return is_valid;
}
