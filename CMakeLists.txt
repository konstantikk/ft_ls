cmake_minimum_required(VERSION 3.17)
project(ft_ls C)

set(CMAKE_C_STANDARD 99)

add_executable(tests ./testing_stuff/main.c)

add_executable(ft_ls    ft_ls_v1/src/args_parse.c
                        ft_ls_v1/src/node_init.c
                        ft_ls_v1/src/main.c
                        ft_ls_v1/src/read_nodes.c
                        ft_ls_v1/src/print_nodes.c
                        ft_ls_v1/src/read_nodes.c
                        ft_ls_v1/src/sort_nodes.c
                        ft_ls_v1/src/processing_dir_output.c
                        ft_ls_v1/src/processing_file_output.c
                        ft_ls_v1/src/generate_output.c
                        ft_ls_v1/src/output_utils.c
                        ft_ls_v1/src/utils.c)

target_include_directories(ft_ls PUBLIC ./ft_ls_v1/libft/includes)
target_include_directories(ft_ls PUBLIC ./ft_ls_v1/includes)

target_link_libraries(ft_ls /home/professor/SchoolProjects/ft_ls/ft_ls_v1/libft/libft.a)
