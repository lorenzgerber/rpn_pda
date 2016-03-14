cmake_minimum_required(VERSION 3.3)
project(rpn_pda)

set(CMAKE_C_FLAGS "-std=c99")

set(SOURCE_FILES main.c pda.c state.c transition.c
        table.c dlist.c stack_1cell.c)
add_executable(rpn_pda ${SOURCE_FILES} main.c)