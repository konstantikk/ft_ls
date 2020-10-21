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
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

///define current dir
#define CURRENT_DIR "."

#define MAX_TYPES_NUM DT_SOCK + 1
#define PERMISSION_FIELDS_NUM 9
#define USERS_COUNT 3
#define ONE_USER_MASK 0x7u
#define ONE_USER_SHIFT 3u
#define NO_NEWLINE_AND_SECS 9

#define READ 'r'
#define WRITE 'w'
#define EXECUTE 'x'
#define NONE '-'


typedef struct dirent t_dirent;
typedef struct stat	  t_stat;

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


/**
 *  node struct will have these fields:
 *  d_type
 *  st_mode
 *  st_nlink
 *  st_uid
 *  st_gid
 *  st_size
 *  st_mtim.tv_sec
 *  d_name
 *  maybe we will need more fields but that is enough to implement  -l flag
 *  also we will need block size for each file, gonna add soon this
 *
 *  prefix d - means the values has come from readdir
 *  prefix st means the values has come from stat
 *
 *  maybe we should just make struct wrapper around t_dirent and stat
 */

typedef struct s_node {
	t_dirent* d;
	t_stat* st;
} 			   t_node;

typedef struct s_handler {
	t_pvec* dir_vec;
	t_dirent* read_ptr;
} 				t_handler;

void print_node(const t_dirent* dir);

#endif //FT_LS_FT_LS_H
