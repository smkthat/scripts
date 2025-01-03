# Variables
V=0.0.1
VERSION=$(V)
STAGE=dev # dev | debug | tests | release
BUILD_POSTFIX=$(strip $(STAGE)_$(VERSION))

# Define project paths
PWD:=$(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRC_DIR=$(PWD)src/
TESTS_DIR=$(PWD)tests/
BUILD_DIR=$(PWD)build/
BUILD_TESTS_DIR=$(PWD)build/tests/
LOGS_DIR=$(PWD)logs/

# Check gcc installing
CC:=$(shell which gcc 2>/dev/null)
ifeq ($(CC),)
$(error "gcc not found. Please install gcc or ensure it is in your PATH.")
endif

# Options
CC_FLAGS=-Wall -Werror -Wextra -std=c11
CC_DEBUG_FLAGSS=-g -O0 -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
CPPCHECK_FLAGS=--enable=all --std=c11 --suppress=missingIncludeSystem --suppress=unusedFunction

# Show current configuration
config:
	@echo "\n\033[1;32mMakefile $(V)\033[0m"
	@echo
	@echo
	@echo "\033[0;32mCommands\033[0m \033[3m(main commands)\033[0m"
	@echo
	@printf "  \033[0;33m%-15s\033[0m - %s\n" "make build" "Run build target stage"
	@printf "  \033[0;33m%-15s\033[0m - %s\n" "make check" "Run clang and cpp checks"
	@printf "  \033[0;33m%-15s\033[0m - %s\n" "make format" "Run clang formatting"
	@printf "  \033[0;33m%-15s\033[0m - %s\n" "make config" "(this) Show current Makefile configuration"
	@printf "  \033[0;33m%-15s\033[0m - %s\n" "make v" "Show current Makefile version"
	@echo
	@echo
	@echo "\033[0;32mVariables\033[0m \033[3m(variables for using with commands)\033[0m"
	@echo
	@printf "  %-15s - %s\n" "STAGE" "[ dev | debug | tests | release ]"
	@printf "  %-15s - %s\n" "VERSION" "Any text"
	@printf "  %-15s - %s\n" "BUILD_POSTFIX" "Replace \"%STAGE_%VERSION\" pattern"
	@echo
	@echo "  \033[3mUsage example\033[0m:"
	@echo "  > make build STAGE=release VERSION=1.2"
	@echo
	@echo
	@echo "\033[0;32mCompiler\033[0m \033[3m(current gcc configuration)\033[0m"
	@echo
	@printf "  %-15s %s\n" "gcc" "$(CC)"
	@printf "  %-15s %s\n" "build_flags" "$(CC_FLAGS)"
	@printf "  %-15s %s\n" "debug_flags" "$(CC_DEBUG_FLAGSS)"
	@echo
	@echo
	@echo "\033[0;32mPaths\033[0m \033[3m(current working abs paths)\033[0m"
	@echo
	@printf "  %-15s %s\n" "root" "$(PWD)"
	@printf "  %-15s %s\n" "src" "$(SRC_DIR)"
	@printf "  %-15s %s\n" "tests" "$(TESTS_DIR)"
	@printf "  %-15s %s\n" "logs" "$(LOGS_DIR)"
	@printf "  %-15s %s\n" "build" "$(BUILD_DIR)"
	@printf "  %-15s %s\n" "build/tests" "$(BUILD_TESTS_DIR)"

build: v
	@echo "\033[0;32mStart building project\033[0m"
	@echo "stage=\033[0;33m$(STAGE)\033[0m"
	@echo "version=\033[0;33m$(VERSION)\033[0m"

test_lib:
	$(CC) $(CC_FLAGS) $(CC_DEBUG_FLAGSS) ./src/input_lib/*.c ./src/tests_lib/*.c ./tests/test_input_lib.c -o $(BUILD_TESTS_DIR)tests.out
	$(BUILD_TESTS_DIR)tests.out
	$(CC) $(CC_FLAGS) $(CC_DEBUG_FLAGSS) ./src/array_lib/*.c ./src/tests_lib/*.c ./tests/test_array_lib.c -o $(BUILD_TESTS_DIR)tests.out
	$(BUILD_TESTS_DIR)tests.out

# Run clang and cpp checks
check:
	@printf "+--------------------+\n│ %-20s │\n+--------------------+\n\n" "💅 clang check"
	@if clang-format -n $(SRC_DIR)**/*.[ch]; then \
		echo "\033[0;32mNo style errors found.\033[0m\n\n"; \
	else \
		"\033[0;31mStyle errors detected! Please run `make format` to fix them.\033[0m\n\n"; \
		exit 1; \
	fi
	@printf "+--------------------+\n│ %-20s │\n+--------------------+\n\n" "📋 cpp check"
	cppcheck $(CPPCHECK_FLAGS) --checkers-report=$(LOGS_DIR)cppcheck_src.log $(SRC_DIR)
	cppcheck $(CPPCHECK_FLAGS) --suppress=ignoredReturnValue --checkers-report=$(LOGS_DIR)cppcheck_tests.log $(TESTS_DIR)
	@echo "\n\033[0;32mAll checks complete.\033[0m";

# Run clang formatting
format:
	@printf "+--------------------+\n│ %-20s │\n+--------------------+\n" "💅 clang format"
	@echo clang-format -i $(SRC_DIR)**/*.[ch]
	@echo clang-format -i $(TESTS_DIR)*.[ch] $(TESTS_DIR)**/*.[ch]
	@find $(SRC_DIR) -type f \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +
	@find $(TESTS_DIR) -type f \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +
	@echo "\n\033[0;32mFormat complete.\033[0m\n\n";


# Show current Makefile version
v:
	@echo $(V)
