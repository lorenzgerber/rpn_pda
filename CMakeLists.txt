cmake_minimum_required(VERSION 3.3)
project(rpn_pda)

set(CMAKE_C_FLAGS "-std=c99")

set(SOURCE_FILES rpn_automat.c pda.c state.c transition.c
        table.c dlist.c stack_1cell.c functions.c validator.c calculator.c)
add_executable(rpn_automat ${SOURCE_FILES} rpn_automat.c)