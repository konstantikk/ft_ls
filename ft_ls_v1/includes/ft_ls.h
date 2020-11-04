//
// Created by professor on 10/9/20.
//

#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#if defined(__APPLE__) || defined(__NetBSD__)
#define st_atim st_atimespec
#define st_ctim st_ctimespec
#define st_mtim st_mtimespec
#endif

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
///define current node
#define CURRENT_NODE  ((t_node*)handler->processed_nodes->data[handler->processed_nodes->length - 1])

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


///macroses to access flags
#define ALPHABET_SIZE 26

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
	///global fields
	///s_node
	t_pvec* nodes;
	size_t total;
	///char path[256]; ??

	///t_dirent
	char d_name[256];
	unsigned char d_type;

	///t_stat
	__mode_t st_mode;
	__nlink_t st_nlink;
	__uid_t st_uid;
	__gid_t st_gid;
	__off_t st_size;
	struct timespec st_mtim;
} 			   t_node;

typedef struct  s_dir {
	///s_node vector
}				t_dir;

/**current flags map
 * 							  76543210
 * 00000000 00000000 00000000 00000000
 * 								taRrl
 * 	update after each added flag!!!!!
 */

#define LIST 0x2u
#define REVERSE_SORT 0x4u
#define RECURSIVE 0x8u
#define ALL_NODES 0x10u
#define TIME_SORT 0x20u

/**
 * input_nodes will be a vector of char* of nodes the came from the input
 * processed_nodes will be ready to print structures with all necessary data
 */

typedef struct s_handler {
	t_pvec* input_nodes;
	t_pvec* processed_nodes;
	unsigned int flags;
} 				t_handler;

void print_node(const t_dirent* dir);
void parse_input(int argc, char** argv, t_handler *handler);
void read_nodes(t_handler *handler);
void finish_him();
#endif //FT_LS_FT_LS_H
