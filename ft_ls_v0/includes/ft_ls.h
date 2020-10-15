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

/**
 * node struct that will contain all info needed for the output and sorting
 */

typedef struct s_node {
	int mode;
	char* name;
} 			   t_node;

typedef struct s_handler {
	t_pvec* dir_vec;
	t_dirent* read_ptr;
} 				t_handler;

#endif //FT_LS_FT_LS_H
