cmake_minimum_required(VERSION 3.10)
project(bao_caoktlt C)

set(CMAKE_C_STANDARD 99)

add_executable(bao_caoktlt main.c menu.c xuly.c tichphan.c phu.c)
target_link_libraries(bao_caoktlt m)
target_link_libraries(bao_caoktlt ncurses)