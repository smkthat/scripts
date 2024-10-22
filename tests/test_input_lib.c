#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/input_lib/input_lib.h"
#include "../src/tests_lib/tests_fixture.h"
#include "../src/tests_lib/tests_logger.h"

void test_input_str() {
    char *input = NULL;

    read_file_in_stdin("tests/test_data/input_lib/test_input_str.txt");

    input = input_str(input);
    assert(strcmp(input, "hello") == 0);

    free(input);
}

void test_input_digit() {
    int number;

    read_file_in_stdin("tests/test_data/input_lib/test_input_digit.txt");

    int result = input_digit(&number);
    assert(result == 1);
    assert(number == 42);
}

int main() {
    run_test((Test)test_input_str, 1, 2, "test_input_str");
    run_test((Test)test_input_digit, 2, 2, "test_input_digit");
    printf("All %d/%d tests passed!\n", 2, 2);
    return 0;
}
