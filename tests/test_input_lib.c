#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/input_lib/input_lib.h"
#include "../src/tests_lib/tests_fixture.h"
#include "../src/tests_lib/tests_logger.h"

void test_scan_input_characters() {
    int size = 10;
    char *input = (char *)calloc(size, sizeof(char));
    assert(input != NULL);

    read_file_in_stdin("tests/test_data/input_lib/test_scan_input_characters.txt");

    input = scan_input_characters(input, &size);

    assert(input != NULL);
    assert(strcmp(input, "hello") == 0);

    free(input);
}

void test_input_string() {
    int size = 10;
    char *input = input_sting(size);
    assert(input != NULL);

    read_file_in_stdin("tests/test_data/input_lib/test_input_string.txt");

    assert(strcmp(input, "hello") == 0);

    free(input);
}

void test_input_single_digit() {
    int number;

    read_file_in_stdin("tests/test_data/input_lib/test_input_single_digit.txt");

    int result = input_single_digit(&number);
    assert(result == 1);
    assert(number == 42);
}

int main() {
    run_test((Test)test_scan_input_characters, 1, 3, "test_scan_input_characters");
    run_test((Test)test_input_string, 2, 3, "test_input_string");
    run_test((Test)test_input_single_digit, 3, 3, "test_input_single_digit");
    printf("All %d/%d tests passed!\n", 3, 3);
    return 0;
}
