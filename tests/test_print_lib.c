#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "../src/print_lib/print_box.h"
#include "../src/tests_lib/tests_case.h"
#include "../src/tests_lib/tests_stdout.h"

int test_init_print_box() {
    int test_result = TEST_FAIL;

    PrintBox *box = init_print_box(20, NULL, PRINTBOX_BORDER_SIMPLE, 0);
    if (box != NULL) {
        test_result = (box->width == 20 && strcmp(box->locale, PRINTBOX_DEFAULT_LOCALE) == 0);
        destroy_print_box(box);
    }

    return test_result;
}

int test_set_border_characters() {
    int test_result = TEST_FAIL;

    PrintBox *box =
        init_print_box(20, NULL, PRINTBOX_BORDER_CUSTOM, 0, L'#', L'#', L'#', L'#', L'#', L'#', L'-', L'|');
    if (box) {
        test_result = (box->tl_corner == L'#' && box->tr_corner == L'#' && box->h_corner == L'-' &&
                       box->v_corner == L'|');
        destroy_print_box(box);
    }

    return test_result;
}

int test_print_header_line_with_text() {
    int test_result = TEST_FAIL;

    StdoutComparator *comparator = init_comparator(PRINTBOX_DEFAULT_BUFFER, WCHAR_TYPE);
    if (redirect_stdout(comparator, "tests/test_data/print_lib/test_print_header_line_with_text.tmp")) {
        PrintBox *box = init_print_box(80, NULL, PRINTBOX_BORDER_SINGLE, 0);
        if (box) {
            print_header_line_with_text(box, L"test_print_header_line_with_text");
            destroy_print_box(box);
        }

        if (catch_stdout(comparator)) {
            test_result = compare_with_file(comparator,
                                            "tests/test_data/print_lib/test_print_header_line_with_text.txt");
        }

        destroy_comparator(comparator);
        // remove(tmp_path);
    }

    return test_result;
}

int test_print_footer_line_with_text() {
    int test_result = TEST_FAIL;

    StdoutComparator *comparator = init_comparator(PRINTBOX_DEFAULT_BUFFER, WCHAR_TYPE);
    if (redirect_stdout(comparator, "tests/test_data/print_lib/test_print_footer_line_with_text.tmp")) {
        PrintBox *box = init_print_box(80, NULL, PRINTBOX_BORDER_SINGLE, 0);
        if (box) {
            print_footer_line_with_text(box, L"test_print_footer_line_with_text");
            destroy_print_box(box);
        }

        if (catch_stdout(comparator)) {
            test_result = compare_with_file(comparator,
                                            "tests/test_data/print_lib/test_print_footer_line_with_text.txt");
        }

        destroy_comparator(comparator);
        // remove(tmp_path);
    }

    return test_result;
}

int test_print_text() {
    int test_result = TEST_FAIL;

    StdoutComparator *comparator = init_comparator(PRINTBOX_DEFAULT_BUFFER, WCHAR_TYPE);
    if (redirect_stdout(comparator, "tests/test_data/print_lib/test_print_text.tmp")) {
        PrintBox *box = init_print_box(80, NULL, PRINTBOX_BORDER_SINGLE, 0);
        if (box) {
            print_text(box, L"test_print_text");
            destroy_print_box(box);
        }

        if (catch_stdout(comparator)) {
            test_result = compare_with_file(comparator, "tests/test_data/print_lib/test_print_text.txt");
        }

        destroy_comparator(comparator);
        // remove(tmp_path);
    }

    return test_result;
}

int test_print_text_without_wordwrap() {
    int test_result = TEST_FAIL;

    StdoutComparator *comparator = init_comparator(PRINTBOX_DEFAULT_BUFFER, WCHAR_TYPE);
    if (redirect_stdout(comparator, "tests/test_data/print_lib/test_print_text_without_wordwrap.tmp")) {
        PrintBox *box = init_print_box(16, NULL, PRINTBOX_BORDER_SINGLE, 0);
        if (box) {
            print_text(box, L"test_print_text_without_wordwrap");
            destroy_print_box(box);
        }

        if (catch_stdout(comparator)) {
            test_result = compare_with_file(comparator,
                                            "tests/test_data/print_lib/test_print_text_without_wordwrap.txt");
        }

        destroy_comparator(comparator);
        // remove(tmp_path);
    }

    return test_result;
}

int test_print_formatted_text() {
    int test_result = TEST_FAIL;

    StdoutComparator *comparator = init_comparator(PRINTBOX_DEFAULT_BUFFER, WCHAR_TYPE);
    if (redirect_stdout(comparator, "tests/test_data/print_lib/test_print_formatted_text.tmp")) {
        PrintBox *box = init_print_box(80, NULL, PRINTBOX_BORDER_SINGLE, 1);
        if (box) {
            print_formatted_text(box, L"%ls_%ls_%ls_%ls", L"test", L"print", L"formatted", L"text");
            destroy_print_box(box);
        }

        if (catch_stdout(comparator)) {
            test_result =
                compare_with_file(comparator, "tests/test_data/print_lib/test_print_formatted_text.txt");
        }

        destroy_comparator(comparator);
        // remove(tmp_path);
    }

    return test_result;
}

int main() {
    int is_success = TEST_FAIL;
    Test *test =
        init_test(L"test_print_lib",
                  L"These test cases perform unit testing of the \"print_lib\" library functionality", 7,
                  (TestCase)test_init_print_box, L"test_init_print_box", (TestCase)test_set_border_characters,
                  L"test_set_border_characters", (TestCase)test_print_header_line_with_text,
                  L"test_print_header_line_with_text", (TestCase)test_print_footer_line_with_text,
                  L"test_print_footer_line_with_text", (TestCase)test_print_text, L"test_print_text",
                  (TestCase)test_print_text_without_wordwrap, L"test_print_text_without_wordwrap",
                  (TestCase)test_print_formatted_text, L"test_print_formatted_text");

    if (test != NULL) {
        run_test(test);
        is_success = test->total == test->complete && test->fail == 0;
        destroy_test(test);
    }

    return is_success ? 0 : 1;
}