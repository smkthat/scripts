#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/array_lib/array.h"
#include "../src/tests_lib/tests_case.h"
#include "../src/tests_lib/tests_fixture.h"

#define INT32_ZEROSIZE_PUSH_CASE 0x12345678

int test_array_int32_zerosize_push() {
    array_t *arr = array_new(sizeof(int32_t));
    if (!arr) return TEST_FAIL;
    int result = TEST_PASSED;
    int val = INT32_ZEROSIZE_PUSH_CASE;
    result &= array_push_back(arr, &val);
    result &= *(int32_t *)array_at(arr, 0) == INT32_ZEROSIZE_PUSH_CASE;
    array_destroy(arr);
    return result;
}

int main() {
    Test *test =
        init_test("test_array_lib",
                  " These test cases perform unit testing\n of the \"array_lib\" library functionality", 1,
                  (TestCase)test_array_int32_zerosize_push, "test_array_int32_zerosize_push");
    if (test) {
        run_test(test);
        destroy_test(test);
    }
    return 0;
}
