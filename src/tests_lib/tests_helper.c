#include <stdio.h>
#include <stdlib.h>

int read_file_in_stdin(const char* path) {
    int is_success = (path && freopen(path, "r", stdin));

    if (!is_success) {
        perror("Error opening file");
    }

    return is_success;
}