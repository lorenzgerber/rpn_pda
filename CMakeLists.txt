cmake_minimum_required(VERSION 3.3)
project(rpn_pda)

set(CMAKE_C_FLAGS "-std=c99")

set(SOURCE_FILES rpn_pda.c)
add_executable(rpn_pda ${SOURCE_FILES} rpn_pda.c)