#ifndef TESTS_CASE_H
#define TESTS_CASE_H

#define TEST_PASSED 1
#define TEST_FAIL 0

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

#include "../print_lib/print_box.h"

typedef int (*TestCase)(void);

typedef struct {
    const wchar_t* name;
    const wchar_t* desc;
    int total;
    int complete;
    int passed;
    int fail;

    TestCase* cases;
    wchar_t** cases_names;
    PrintBox* print_box;
} Test;

Test* init_test(const wchar_t* name, const wchar_t* desc, const int total, ...);

Test* run_test(Test* test);

void destroy_test(Test* test);

int run_test_case(TestCase case_func, const int case_number, const int cases_size, const wchar_t* case_name,
                  PrintBox* print_box);

#endif