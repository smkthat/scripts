#include "../src/array_lib/array.h"
#include "../src/tests_lib/tests_case.h"
#include "../src/tests_lib/tests_helper.h"

#define INT32_ZEROSIZE_PUSH_CASE 0x12345678
#define INT64_ZEROSIZE_PUSH_CASE 0x123456789ABCDEF0
#define INT32_SIZE1_PUSH_CASE 0x02134657

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
    Test *test = init_test("test_array_lib",
                           " These test cases perform unit testing\n of the \"array\" library functionality",
                           3, (TestCase)test_array_int32_zerosize_push, "test_array_int32_zerosize_push",
                           (TestCase)test_array_int64_zerosize_push, "test_array_int64_zerosize_push",
                           (TestCase)test_array_int32_size1_push, "test_array_int32_size1_push");
    if (test) {
        run_test(test);
        destroy_test(test);
    }
    return 0;
}
