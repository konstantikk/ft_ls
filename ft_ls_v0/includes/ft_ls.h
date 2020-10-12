//
// Created by professor on 10/9/20.
//

#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

///define current dir
#define CURRENT_DIR "."

typedef struct dirent t_dirent;

///in case we will need more execution enums to make our lives easier
typedef enum e_exec {
	NO_DIRS_IN_ARGS,
	DIRS_IN_ARGS
} 			 t_exec;


///handler struct is a main struct in ft_ls
///probably will need a vector of DIRs in case of argc > 2
///also will need int for flags  or mb char will be enough

///will need macros for convenient access to the fields of structs (mb)
typedef struct  s_dir // can be a single file
{
    char *dir_name; // name of main directory
    char *output_line; // formatted string for final output in this directory
    int *time; //time created directory or file, key for sorting, maybe it's not int

}               t_dir;

typedef struct s_handler // main struct for project
{

	t_pvec* dir_vec; // one node is struct t_dir
	t_dirent* read_ptr; //adjacent vector, each node contains files contains in directory
	unsigned int flag_r: 1;
	unsigned  int flag_t: 1;
    unsigned  int flag_recursive: 1;
    unsigned  int flag_l: 1;
    unsigned  int flag_a: 1;

} 				t_handler;

#endif //FT_LS_FT_LS_H
