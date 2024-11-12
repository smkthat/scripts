#include "tests_case.h"

Test* init_test(const wchar_t* name, const wchar_t* desc, const int total, ...) {
    Test* test = (Test*)malloc(sizeof(Test));
    if (test) {
        test->name = name;
        test->desc = desc;
        test->total = total;
        test->complete = 0;
        test->passed = 0;
        test->fail = 0;
        test->cases = calloc(total, sizeof(TestCase));
        test->cases_names = calloc(total, sizeof(wchar_t*));
        test->print_box = init_print_box(76, NULL, PRINTBOX_BORDER_SINGLE, 1);

        if (test->cases && test->cases_names && test->print_box) {
            va_list args;
            va_start(args, total);
            for (int i = 0; i < total; i++) {
                test->cases[i] = va_arg(args, TestCase);
                test->cases_names[i] = va_arg(args, wchar_t*);
            }
            va_end(args);
        } else {
            free(test);
            test = NULL;
        }
    }

    return test;
}

Test* run_test(Test* test) {
    if (!test || !test->print_box) {
        return test;
    }

    print_header_line_with_text(test->print_box, test->name);
    print_text(test->print_box, L"");
    print_text(test->print_box, test->desc);
    print_text(test->print_box, L"");

    for (int i = 0; i < test->total; i++) {
        TestCase test_case = test->cases[i];
        int is_passed = run_test_case(test_case, i + 1, test->total, test->cases_names[i], test->print_box);

        if (is_passed) {
            test->passed += 1;
        } else {
            test->fail += 1;
        }

        test->complete += 1;
    }

    printf_text(test->print_box, L"\nTotal cases %d, Completed %d, Passed %d, Failed %d\n\n%ls", test->total,
                test->complete, test->passed, test->fail,
                test->total == test->passed ? L"✓ All tests passed!" : L"✗ Cases completed with errors.");
    print_footer_line(test->print_box);

    return test;
}

void destroy_test(Test* test) {
    if (test) {
        free(test->cases);
        free(test->cases_names);
        destroy_print_box(test->print_box);
        free(test);
    }
}

int run_test_case(TestCase case_func, const int case_number, const int cases_size, const wchar_t* case_name,
                  PrintBox* print_box) {
    clock_t start_time = clock();
    int is_passed = case_func();
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf_text(print_box, L"%ls %d/%d - %-40ls %-6ls in %.2f seconds.", is_passed ? L"✓" : L"✗", case_number,
                cases_size, case_name, is_passed ? L"PASSED" : L"FAIL", time_taken);

    return is_passed;
}