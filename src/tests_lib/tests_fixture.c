#include <stdio.h>
#include <stdlib.h>

void read_file_in_stdin(const char* path) {
    if (freopen(path, "r", stdin) == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
}