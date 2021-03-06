//
// Created by professor on 10/9/20.
//

#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#if defined(__APPLE__) || defined(__NetBSD__)
#define st_atim st_atimespec
#define st_ctim st_ctimespec
#define st_mtim st_mtimespec
#define __off_t off_t
#define __gid_t gid_t
#define __uid_t uid_t
#define __uint16_t uint16_t
#define __nlink_t nlink_t
#define __darwin_mode_t darwin_mode_t
#define __mode_t mode_t
#define __blksize_t blksize_t
#define __blkcnt_t blkcnt_t
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
///define NODE macro might need to specify where from to take an elem
///further expand
#define NODE(vec,idx)  ((t_node*)((vec)->data[idx]))
#define CURRENT_NODE ((t_node*)(dir->nodes->data[dir->nodes->length - 1]))

#define MAX_FILENAME_SIZE 256

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
typedef struct tm     t_full_time;

///in case we will need more execution enums to make our lives easier
typedef enum e_exec {
	LOCAL,
	GLOBAL,
	NO_OPTION,
	CANT_OPEN
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

	///custom
	char full_path[MAX_FILENAME_SIZE];
	///when readlink is happening this is where the result SHOULD be placed
	///so for symbolic links there will be 3 names:
	///										local link_name
	///										global link_name
	///										where link links to
	char links_to[MAX_FILENAME_SIZE];
	///in some cases we need to know if full path is set thats why I added
	///this bool var for easy access and no heuristic
	///like checking first element of the char array
	int full_path_is_set:1;

	///for output purpose
	size_t local_max_filename_len;
	size_t full_path_len;
	size_t d_name_len;

	///t_dirent
	char d_name[MAX_FILENAME_SIZE];
	unsigned char d_type;


	///t_stat
	__mode_t st_mode;
	__nlink_t st_nlink;
	__uid_t st_uid;
	__gid_t st_gid;
	__off_t st_size;
	__blkcnt_t st_blocks;
	__blksize_t st_blksize;
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
	///vec to hold input data
	t_pvec* input_nodes;
	///vec to hold 'ready to output' data
	t_pvec* processed_nodes;
	///var to count files to sort in the end
	int files_num;
	///for output purpose
	size_t global_max_filename_len;
	///configuration of execution
	unsigned int flags;
	///vec for output with l flag
    t_pvec      *output_vec_util;
    ///int array for output with l flag
    int         *output_max_list_util;
    ///char vector for output
    t_cvec      *output_str;
} 				t_handler;

void print_node(const t_dirent* dir);
void parse_input(int argc, char** argv, t_handler *handler);
void read_nodes(t_handler *handler);
void sort_nodes(t_node** nodes, const int begin, const int end, unsigned int flags, const t_exec sort_type);
void copy_info(t_node* node, t_stat* st);
void get_node_info(t_node* node);
void debug_read_nodes(t_handler* handler, t_pvec* processed_nodes);
t_node* init_node(const char* prefix, const char* node_name, unsigned char d_type);
t_node* init_node_and_get_info(const char* prefix, const char* node_name, unsigned char d_type);
void set_fullpath(t_node* node, const char* prefix, const char* node_name);
size_t get_max_filename_len(t_pvec* nodes, const t_exec max_type);
unsigned char st_mode2d_type(__mode_t mode);
void finish_him();
void error_manager(const char* inv_piece, t_exec error_type);


void output_manager(t_handler *handler, t_pvec *processed_node);
char* print_time(const time_t *time);
char* print_permissions(mode_t st_mode);
char print_type(const unsigned char d_type);

int     find_max(t_pvec * nodes);
void    init_list(t_pvec *vec, char *res, int *max);
void    collect_inf(t_node *node, t_pvec *vec, int *max);
void    collect_files(t_cvec *output_str, t_node *node, size_t max, int last_flag);
void    add_to_output(t_cvec *output_str, t_pvec *vec, int *max_list);
void    files_processing(t_node *node, t_handler *handler, size_t p_len, size_t i);
void    directory_processing(t_node *node, t_handler *handler, size_t p_len, size_t i);
#endif //FT_LS_FT_LS_H
