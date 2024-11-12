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
    if (box != NULL) {
        test_result = (box->tl_corner == L'#' && box->tr_corner == L'#' && box->h_corner == L'-' &&
                       box->v_corner == L'|');
        destroy_print_box(box);
    }

    return test_result;
}

int test_print_header_line_with_text() {
    int test_result = TEST_FAIL;

    PrintBox *box = init_print_box(80, NULL, PRINTBOX_BORDER_SINGLE, 0);
    if (box != NULL) {
        void *original_stdout = stdout;
        const char *tmp_file_path = "tests/test_data/print_lib/test_print_header_line_with_text.tmp";

        FILE *fp = freopen(tmp_file_path, "w+", stdout);
        if (fp != NULL) {
            print_header_line_with_text(box, L"test_print_lib");
            fflush(stdout);

            fseek(fp, 0, SEEK_SET);
            wchar_t buffer[PRINTBOX_DEFAULT_BUFFER];
            fgetws(buffer, PRINTBOX_DEFAULT_BUFFER, fp);

            test_result = (wcscmp(buffer,
                                  L"┌───────────────────────────────── test_print_lib "
                                  L"─────────────────────────────────┐\n") == 0);

            fclose(fp);
            freopen("/dev/tty", "w", original_stdout);
            // remove(tmp_file_path);
        }

        destroy_print_box(box);
    }

    return test_result;
}

int test_print_text() {
    int test_result = TEST_FAIL;

    PrintBox *box = init_print_box(80, NULL, PRINTBOX_BORDER_SINGLE, 0);
    if (box != NULL) {
        void *original_stdout = stdout;
        const char *tmp_file_path = "tests/test_data/print_lib/test_print_text.tmp";

        FILE *fp = freopen(tmp_file_path, "w+", stdout);
        if (fp != NULL) {
            print_text(box, L"test_print_lib");
            fflush(stdout);

            fseek(fp, 0, SEEK_SET);
            wchar_t buffer[PRINTBOX_DEFAULT_BUFFER];
            fgetws(buffer, PRINTBOX_DEFAULT_BUFFER, fp);

            test_result = (wcscmp(buffer,
                                  L"│ test_print_lib                                                         "
                                  L"          │\n") == 0);

            fclose(fp);
            freopen("/dev/tty", "w", original_stdout);
            // remove(tmp_file_path);
        }

        destroy_print_box(box);
    }

    return test_result;
}

int main() {
    int is_success = TEST_FAIL;
    Test *test =
        init_test(L"test_print_lib",
                  L"These test cases perform unit testing of the \"print_lib\" library functionality", 4,
                  (TestCase)test_init_print_box, L"test_init_print_box", (TestCase)test_set_border_characters,
                  L"test_set_border_characters", (TestCase)test_print_header_line_with_text,
                  L"test_print_header_line_with_text", (TestCase)test_print_text, L"test_print_text");

    if (test != NULL) {
        run_test(test);
        is_success = test->total == test->complete && test->fail == 0;
        destroy_test(test);
    }

    return is_success ? 0 : 1;
}