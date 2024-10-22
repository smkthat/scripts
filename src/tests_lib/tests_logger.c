#include "tests_logger.h"

#include <stdio.h>
#include <time.h>

void run_test(Test test, const int case_n, const int cases_size, const char *name) {
    printf("[%d/%d] Starting test: '%s'\n", case_n, cases_size, name);

    clock_t start_time = clock();

    test();

    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Test completed successfully in %.2f seconds.\n\n", time_taken);
}