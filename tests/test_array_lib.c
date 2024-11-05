#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/array_lib/array.h"
#include "../src/tests_lib/tests_case.h"
#include "../src/tests_lib/tests_fixture.h"

#define INT16_NEW_FILLED_CASE 0x1234
#define INT32_ZEROSIZE_PUSH_CASE 0x12345678
#define INT64_ZEROSIZE_PUSH_CASE 0x123456789ABCDEF0
#define INT32_SIZE1_PUSH_CASE 0x02134657

int test_array_invalid_element_size_new() {
    array_t *arr0 = array_new(0);
    array_t *arr1 = array_new(-1);
    array_destroy(arr0);
    array_destroy(arr1);
    return arr0 == NULL && arr1 == NULL;
}

int test_array_int16_new_filled() {
    int16_t val = INT16_NEW_FILLED_CASE;
    array_t *arr = array_new_filled(sizeof(int16_t), 15, &val);
    if (!arr) return TEST_FAIL;
    int result = TEST_PASSED;
    for (int i = 0; i < 15; i++) {
        result &= *(int16_t *)array_at(arr, i) == INT16_NEW_FILLED_CASE;
    }
    array_destroy(arr);
    return result;
}

int test_array_int32_zerosize_push() {
    array_t *arr = array_new(sizeof(int32_t));
    if (!arr) return TEST_FAIL;
    int result = TEST_PASSED;
    int32_t val = INT32_ZEROSIZE_PUSH_CASE;
    result &= array_push_back(arr, &val);
    result &= *(int32_t *)array_at(arr, 0) == INT32_ZEROSIZE_PUSH_CASE;
    array_destroy(arr);
    return result;
}

int test_array_int64_zerosize_push() {
    array_t *arr = array_new(sizeof(int64_t));
    if (!arr) return TEST_FAIL;
    int result = TEST_PASSED;
    int64_t val = INT64_ZEROSIZE_PUSH_CASE;
    result &= array_push_back(arr, &val);
    result &= *(int64_t *)array_at(arr, 0) == INT64_ZEROSIZE_PUSH_CASE;
    array_destroy(arr);
    return result;
}

int test_array_int32_size1_push() {
    array_t *arr = array_new(sizeof(int32_t));
    if (!arr) return TEST_FAIL;
    int result = TEST_PASSED;
    int32_t val = INT32_ZEROSIZE_PUSH_CASE;
    result &= array_push_back(arr, &val);
    val = INT32_SIZE1_PUSH_CASE;
    result &= array_push_back(arr, &val);
    result &= *(int32_t *)array_at(arr, 0) == INT32_ZEROSIZE_PUSH_CASE &&
              *(int32_t *)array_at(arr, 1) == INT32_SIZE1_PUSH_CASE;
    array_destroy(arr);
    return result;
}

int main() {
    Test *test = init_test(
        "test_array_lib", " These test cases perform unit testing\n of the \"array\" library functionality",
        5, (TestCase)test_array_invalid_element_size_new, "test_array_invalid_element_size_new",
        (TestCase)test_array_int16_new_filled, "test_array_int16_new_filled",
        (TestCase)test_array_int32_zerosize_push, "test_array_int32_zerosize_push",
        (TestCase)test_array_int64_zerosize_push, "test_array_int64_zerosize_push",
        (TestCase)test_array_int32_size1_push, "test_array_int32_size1_push");
    if (test) {
        run_test(test);
        destroy_test(test);
    }
    return 0;
}
