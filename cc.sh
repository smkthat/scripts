#!/bin/bash

ascii_art_start() {
    echo "────────────────"
    echo " 🆂 🅲 🅷 🅾 🅾 🅻 21"
    echo "  c-compiler"
    echo "     v.1.1"
    echo "────────────────"
    echo ""
}

log_info() {
    echo -e "\033[1;32mINFO:\033[0m $1"
}

log_error() {
    echo -e "\033[1;31mERROR:\033[0m $1" >&2
}

check_dependencies() {
    command -v clang-format >/dev/null 2>&1 || { log_error "clang-format не установлен."; exit 1; }
    command -v gcc >/dev/null 2>&1 || { log_error "gcc не установлен."; exit 1; }
}

format_code() {
    if [ "$SHOULD_FORMAT" = true ]; then
        log_info "Форматирование..."
        clang-format -n "$1" || { log_error "clang-format обнаружил проблемы."; exit 1; }
        clang-format -i "$1"
    else
        log_info "Форматирование пропущено из-за флага --no-format"
    fi
}

compile_code() {
    log_info "Компиляция..."
    if [ "$SHOULD_MEM_CHECK" = true ]; then
        gcc -g -O0 -Wall -Werror -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable "$1" -o "build/$2" || { log_error "Ошибка компиляции."; exit 1; }
    else
        gcc -g -O0 -Wall -Werror -Wextra "$1" -o "build/$2" || { log_error "Ошибка компиляции."; exit 1; }
    fi
}

run_program() {
    if [ "$SHOULD_START" = true ]; then
        log_info "Запуск $1 ..."
        echo "(для отмены запуска нажмите Ctrl + C)"
        "./build/$1"
    else
        log_info "Запуск пропущен из-за флага --no-start"
    fi
}

show_help() {
    echo "Usage: $0 [options] <file.c|*>"
    echo
    echo "Options:"
    echo "  --no-start       Не запускать программу после компиляции (не применяется при использовании *)."
    echo "  --no-format      Не форматировать код перед компиляцией."
    echo "  --no-mem-check   Не использовать проверку памяти при компиляции."
    echo "  -h, --help       Показать это сообщение и выйти."
    echo
    echo "Пример: $0 --no-format my_program.c"
    echo "Пример: $0 *"
}

main() {
    ascii_art_start

    SHOULD_START=true
    SHOULD_FORMAT=true
    SHOULD_MEM_CHECK=true

    if [ $# -eq 0 ]; then
        log_error "Нет введенных опций или файла."
        show_help
        exit 1
    fi

    while [[ $# -gt 0 ]]; do
        case $1 in
            --no-start)
                SHOULD_START=false
                shift
                ;;
            --no-format)
                SHOULD_FORMAT=false
                shift
                ;;
            --no-mem-check)
                SHOULD_MEM_CHECK=false
                shift
                ;;
            -h|--help)
                show_help
                exit 0
                ;;
            *)
                TARGET_FILE=$1
                SHOULD_START=false
                shift
                ;;
        esac
    done

    echo $TARGET_FILE

    if [ -z "$TARGET_FILE" ]; then
        log_error "Файл не указан"
        exit 1
    fi

    if [ "$TARGET_FILE" = "*" ]; then
        FILES=$(*.c)
        if [ ${#FILES[@]} -eq 0 ]; then
            log_error "Нет C-файлов в текущей директории."
            exit 1
        fi
    else
        FILES=("$TARGET_FILE")
    fi

    check_dependencies

    if ! [ -d ./build ]; then
        mkdir build
    fi

    echo $FILES

    for FILE in "${FILES[@]}"; do
        if [[ ! "$FILE" =~ \.c$ ]]; then
            log_error "Файл $FILE не является C-файлом."
            continue
        fi

        TARGET_FILE_WITHOUT_EXTENSION=$(basename "$FILE" .c)

        log_info "Старт сборки $FILE ..."
        format_code "$FILE"
        compile_code "$FILE" "$TARGET_FILE_WITHOUT_EXTENSION"
        run_program "$TARGET_FILE_WITHOUT_EXTENSION"
    done
}

main "$@"
