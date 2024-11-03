#include "tests_case.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Test* init_test(char* name, char* desc, const int total, ...) {
    Test* test = (Test*)malloc(sizeof(Test));

    if (test == NULL) {
        return NULL;
    }

    test->name = name;
    test->desc = desc;
    test->total = total;
    test->complete = 0;
    test->passed = 0;
    test->fail = 0;
    test->cases = (TestCase*)malloc(total * sizeof(TestCase));
    test->cases_names = (char**)malloc(total * sizeof(char*));

    if (test->cases == NULL || test->cases_names == NULL) {
        free(test);
        return NULL;
    }

    va_list args;
    va_start(args, total);
    for (int i = 0; i < total; i++) {
        test->cases[i] = va_arg(args, TestCase);
        test->cases_names[i] = va_arg(args, char*);
    }
    va_end(args);

    return test;
}

Test* run_test(Test* test) {
    if (test == NULL) {
        return test;
    }

    // TODO: Create a library for print borders
    printf("+--------------------- Test %s ---------------------+\n\n", test->name);
    printf("%s\n\n", test->desc);

    for (int i = 0; i < test->total; i++) {
        TestCase test_case = test->cases[i];
        int is_passed = run_test_case(test_case, i + 1, test->total, test->cases_names[i]);

        if (is_passed) {
            test->passed += 1;
        } else {
            test->fail += 1;
        }

        test->complete += 1;
    }

    printf("\n📋 Total cases %d, Completed %d, Passed %d, Failed %d\n", test->total, test->complete,
           test->passed, test->fail);
    printf("\n%s", test->total == test->passed ? "✅ All tests passed!" : "❌ Tests completed with errors.");
    printf("\n+--------------------------------------------------------------+\n");

    return test;
}

void destroy_test(Test* test) {
    if (test != NULL) {
        free(test->cases);
        free(test->cases_names);
        free(test);
    }
}

int run_test_case(TestCase case_func, const int case_number, const int cases_size, const char* case_name) {
    printf("・ %d/%-2d - %-40s", case_number, cases_size, case_name);

    clock_t start_time = clock();

    int is_passed = case_func();

    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("%s in %.2f seconds.\n", is_passed ? "PASSED" : "FAIL", time_taken);

    return is_passed;
}