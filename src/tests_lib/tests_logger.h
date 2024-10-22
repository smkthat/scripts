#ifndef TESTS_LOGGER_H
#define TESTS_LOGGER_H

typedef void (*Test)(void);

void run_test(Test test, const int case_n, const int cases_size, const char *name);

#endif