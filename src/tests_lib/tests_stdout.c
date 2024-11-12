#include "tests_stdout.h"

StdoutComparator *initialize_comparator(int buffer_size, StdoutDataType data_type) {
    StdoutComparator *comparator = malloc(sizeof(StdoutComparator));
    if (comparator) {
        comparator->original_stdout = stdout;
        comparator->temp_file = NULL;
        comparator->buffer_size = buffer_size;
        comparator->data_type = data_type;

        switch (data_type) {
            case CHAR_TYPE:
                comparator->buffer = calloc(buffer_size, sizeof(char));
                break;
            case WCHAR_TYPE:
                comparator->buffer = calloc(buffer_size, sizeof(wchar_t));
                break;
        }

        if (!comparator->buffer) {
            free(comparator);
            comparator = NULL;
        }
    }

    return comparator;
}

int redirect_stdout(StdoutComparator *comparator, const char *tmp_path) {
    comparator->temp_file = freopen(tmp_path, "w+", stdout);
    return comparator->temp_file != NULL;
}

void catch_stdout(StdoutComparator *comparator) {
    fflush(stdout);
    fseek(comparator->temp_file, 0, SEEK_SET);

    switch (comparator->data_type) {
        case CHAR_TYPE:
            fgets((char *)comparator->buffer, comparator->buffer_size, comparator->temp_file);
            break;
        case WCHAR_TYPE:
            fgetws((wchar_t *)comparator->buffer, comparator->buffer_size, comparator->temp_file);
            break;
    }
}

int compare_files(StdoutComparator *comparator, const char *src_path) {
    FILE *src_file = fopen(src_path, "r");
    int is_success = 0;

    if (src_file) {
        switch (comparator->data_type) {
            case CHAR_TYPE: {
                char *expected_buffer = calloc(comparator->buffer_size, sizeof(char));
                if (expected_buffer) {
                    fgets(expected_buffer, comparator->buffer_size, src_file);
                    is_success = strcmp((char *)comparator->buffer, expected_buffer) == 0;
                    free(expected_buffer);
                }
                break;
            }
            case WCHAR_TYPE: {
                wchar_t *expected_buffer = calloc(comparator->buffer_size, sizeof(wchar_t));
                if (expected_buffer) {
                    fgetws(expected_buffer, comparator->buffer_size, src_file);
                    is_success = wcscmp((wchar_t *)comparator->buffer, expected_buffer) == 0;
                    free(expected_buffer);
                }
                break;
            }
        }
        fclose(src_file);
    }

    return is_success;
}

void restore_stdout(StdoutComparator *comparator) {
#ifdef _WIN32
    freopen("CON", "w", comparator->original_stdout);
#else
    freopen("/dev/tty", "w", comparator->original_stdout);
#endif
}

void cleanup(StdoutComparator *comparator) {
    if (comparator->temp_file) fclose(comparator->temp_file);
    if (comparator->buffer) free(comparator->buffer);
    free(comparator);
}