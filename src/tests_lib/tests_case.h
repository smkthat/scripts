#ifndef TESTS_CASE_H
#define TESTS_CASE_H

#define TEST_PASSED 1
#define TEST_FAIL 0

typedef int (*TestCase)(void);

typedef struct {
    char* name;
    char* desc;
    int total;
    int complete;
    int passed;
    int fail;

    TestCase* cases;
    char** cases_names;
} Test;

Test* init_test(char* name, char* desc, const int total, ...);

Test* run_test(Test* test);

void destroy_test(Test* test);

int run_test_case(TestCase case_func, const int case_number, const int cases_size, const char* case_name);

#endif