#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/input_lib/input_lib.h"
#include "../src/tests_lib/tests_case.h"
#include "../src/tests_lib/tests_fixture.h"

int test_input_str() {
    int test_result = TEST_FAIL;

    char *input = NULL;

    read_file_in_stdin("tests/test_data/input_lib/test_input_str.txt");

    input = input_str(input);
    test_result = (strcmp(input, "hello") == 0);

    free(input);

    return test_result;
}

int test_input_digit() {
    int test_result = TEST_FAIL;

    int number;

    read_file_in_stdin("tests/test_data/input_lib/test_input_digit.txt");

    test_result = (input_digit(&number) == TEST_PASSED && number == 42);

    return test_result;
}

int main() {
    Test *test =
        init_test("test_input_lib",
                  " These test cases perform unit testing\n of the \"input_lib\" library functionality", 2,
                  (TestCase)test_input_str, "test_input_str", (TestCase)test_input_digit, "test_input_digit");

    if (test != NULL) {
        run_test(test);
        destroy_test(test);
    }

    return 0;
}
