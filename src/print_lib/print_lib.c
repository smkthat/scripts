#include "print_lib.h"

PrintBox* init_print_box(int line_width, const char* locale, const int border_type, int word_wrap, ...) {
    PrintBox* box = (PrintBox*)malloc(sizeof(PrintBox));

    if (box) {
        box->max_width = line_width;
        box->locale = locale ? locale : PRINTBOX_DEFAULT_LOCALE;
        box->word_wrap = word_wrap;

        va_list args;
        va_start(args, word_wrap);

        switch (border_type) {
            case PRINTBOX_BORDER_CUSTOM: {
                box->tl_corner = va_arg(args, int);
                box->tr_corner = va_arg(args, int);
                box->mr_corner = va_arg(args, int);
                box->ml_corner = va_arg(args, int);
                box->br_corner = va_arg(args, int);
                box->bl_corner = va_arg(args, int);
                box->h_corner = va_arg(args, int);
                box->v_corner = va_arg(args, int);
                break;
            }
            case PRINTBOX_BORDER_SINGLE: {
                box->tl_corner = L'┌';
                box->tr_corner = L'┐';
                box->mr_corner = L'┤';
                box->ml_corner = L'├';
                box->br_corner = L'┘';
                box->bl_corner = L'└';
                box->h_corner = L'─';
                box->v_corner = L'│';
                break;
            }
            case PRINTBOX_BORDER_DOUBLE: {
                box->tl_corner = L'╔';
                box->tr_corner = L'╗';
                box->ml_corner = L'╠';
                box->mr_corner = L'╣';
                box->br_corner = L'╝';
                box->bl_corner = L'╚';
                box->h_corner = L'═';
                box->v_corner = L'║';
                break;
            }
            case PRINTBOX_BORDER_SIMPLE:
            default: {
                box->tl_corner = L'+';
                box->tr_corner = L'+';
                box->mr_corner = L'+';
                box->ml_corner = L'+';
                box->br_corner = L'+';
                box->bl_corner = L'+';
                box->h_corner = L'–';
                box->v_corner = L'|';
                break;
            }
        }

        setlocale(LC_CTYPE, box->locale);
    }

    return box;
}

void print_header(PrintBox* box) {
    wprintf(L"%lc", box->tl_corner);
    for (int i = 0; i < box->max_width + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->tr_corner);
}

void print_divider(PrintBox* box) {
    wprintf(L"%lc", box->ml_corner);
    for (int i = 0; i < box->max_width + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->mr_corner);
}

void print_footer(PrintBox* box) {
    wprintf(L"%lc", box->bl_corner);
    for (int i = 0; i < box->max_width + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->br_corner);
}

void print_header_with_text(PrintBox* box, const wchar_t* header_text) {
    int padding = (int)(box->max_width - wcslen(header_text) + 2) / 2;
    wprintf(L"%lc", box->tl_corner);
    for (int i = 0; i < padding; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%ls", header_text);
    for (int i = 0; i < box->max_width - padding - (int)wcslen(header_text) + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->tr_corner);
}

void print_divider_with_text(PrintBox* box, const wchar_t* header_text) {
    int padding = (int)(box->max_width - wcslen(header_text) + 2) / 2;
    wprintf(L"%lc", box->ml_corner);
    for (int i = 0; i < padding; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%ls", header_text);
    for (int i = 0; i < box->max_width - padding - (int)wcslen(header_text) + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->mr_corner);
}

void print_footer_with_text(PrintBox* box, const wchar_t* header_text) {
    int padding = (int)(box->max_width - wcslen(header_text) + 2) / 2;
    wprintf(L"%lc", box->bl_corner);
    for (int i = 0; i < padding; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%ls", header_text);
    for (int i = 0; i < box->max_width - padding - (int)wcslen(header_text) + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->br_corner);
}

void print_line(PrintBox* box, const wchar_t* text, unsigned long start_index) {
    wprintf(L"%lc ", box->v_corner);
    unsigned long text_len = wcslen(text);
    unsigned long i = start_index;
    unsigned long printed_chars = 0;
    unsigned long last_space_index = start_index;

    while (i < text_len && printed_chars < box->max_width) {
        if (text[i] == '\n') {
            break;
        }
        if (isspace(text[i])) {
            last_space_index = i;
        }
        wprintf(L"%lc", text[i]);
        i++;
        printed_chars++;
    }

    if (box->word_wrap && i < text_len && !isspace(text[i]) && last_space_index > start_index) {
        i = last_space_index + 1;
        printed_chars = last_space_index - start_index;
        wprintf(L"\r%lc ", box->v_corner);
        for (unsigned long j = start_index; j < i - 1; j++) {
            wprintf(L"%lc", text[j]);
        }
    }

    for (unsigned long j = printed_chars; j < box->max_width; j++) {
        wprintf(L" ");
    }
    wprintf(L" %lc\n", box->v_corner);

    if (i < text_len && text[i] == '\n') {
        i++;
    }

    if (i < text_len) {
        print_line(box, text, i);
    }
}

void print_text(PrintBox* box, const wchar_t* text) { print_line(box, text, 0); }

void destroy_print_box(PrintBox* box) {
    if (box) {
        setlocale(LC_CTYPE, "");
        free(box);
    }
}

int main() {
    wchar_t* text =
        L"\nЗначимость этих проблем настолько очевидна, что сложившаяся структура организации обеспечивает "
        "широкому кругу (специалистов) участие в формировании дальнейших направлений развития. Таким "
        "образом реализация намеченных плановых заданий позволяет выполнять важные задания по разработке "
        "системы обучения кадров, соответствует насущным потребностям.\n\n";
    wchar_t* text2 =
        L"\nЗадача организации, в особенности же постоянное информационно-пропагандистское обеспечение нашей "
        "деятельности позволяет выполнять важные задания по разработке существенных финансовых и "
        "административных условий.\n\n";

    PrintBox* box =
        init_print_box(50, NULL, PRINTBOX_BORDER_SINGLE, 1, L'*', L'*', L'+', L'+', L'*', L'*', L'-', L'|');

    if (!box) {
        fprintf(stderr, "Failed to initialize PrintBox\n");
        return 1;
    }

    print_header_with_text(box, L" Это заголовок текста ");
    print_text(box, text);
    print_divider(box);
    print_text(box, text2);
    print_divider_with_text(box, L" Это подзаголовок ");
    print_text(box, text2);
    print_footer_with_text(box, L" Это подвал текста ");

    destroy_print_box(box);
    return 0;
}
