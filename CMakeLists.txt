cmake_minimum_required(VERSION 3.17)
project(ft_ls C)

set(CMAKE_C_STANDARD 99)

add_executable(ft_ls ./ft_ls_v0/src/main.c)

target_include_directories(ft_ls PUBLIC ./ft_ls_v0/libft/includes)
target_include_directories(ft_ls PUBLIC ./ft_ls_v0/includes)

target_link_libraries(ft_ls /home/professor/ft_ls/ls_easy/libft/libft.a)
