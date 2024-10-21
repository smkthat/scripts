#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/input_lib/input_lib.h"

void test_scan_input_characters() {
    int size = 10;
    char *input = (char *)calloc(size, sizeof(char));
    assert(input != NULL);

    freopen("test_data/input_lib/test_scan_input_characters.txt", "r", stdin);

    input = scan_input_characters(input, &size);
    assert(input != NULL);
    assert(strcmp(input, "hello") == 0);

    free(input);
}

void test_input_string() {
    int size = 10;
    char *input = input_sting(size);
    assert(input != NULL);

    freopen("test_data/input_lib/test_input_string.txt", "r", stdin);

    assert(strcmp(input, "hello") == 0);

    free(input);
}

void test_input_single_digit() {
    int number;

    freopen("test_data/input_lib/test_input_string.txt", "r", stdin);

    int result = input_single_digit(&number);
    assert(result == 1);
    assert(number == 42);
}

int main() {
    test_scan_input_characters();
    test_input_string();
    test_input_single_digit();

    printf("All tests passed!\n");
    return 0;
}
