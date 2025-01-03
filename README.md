# C lang custom Libs & Utils

This repository is a collection of useful tools that were formed to solve various tasks while studying the C language.


## Project structure

```
project_root/
├── build/
|   ├── tests/
|   |   └── <tests_exec_files>
│   └── <src_exec_files>
├── src/
│   ├── input_lib/
│   │   ├── input_lib.c
│   │   └── input_lib.h
│   ├── tests_lib/
│   │   ├── tests_fixture.c
│   │   ├── tests_fixture.h
│   │   ├── tests_cases.c
│   │   └── tests_cases.h
│   └── <other_libs>
├── tests/
│   ├── test_input_lib.c
│   ├── test_data/
│   │   └── <test_data_dirs_&_files>
│   └── <other_tests>
├── .clang-format
├── .gitignore
├── LICENSE
├── Makefile
└── README.md
```
