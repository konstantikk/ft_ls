//
// Created by professor on 10/31/20.
//
#include "ft_ls.h"

/**
 * issues we are facing:
 *  	1) output name of the directory that we are parsing then the content of it
 *  	2) path creation should be rewritten
 *  	3) 1 node -> no name in header, name in header - need to implement
 *  	4) correct error management
 *  	5) total must be divided by 2
 *  	WIP
 */

void get_file(t_handler* handler, const char* file_name, t_stat* st) {
	t_node* node_content;

	if (!(handler->flags & ALL_NODES) && file_name[0] == '.')
		return ;
	///in files which came as args the type is in st
	node_content = init_node("", file_name, st_mode2d_type(st->st_mode));

	///get additional info
	if (handler->flags & LIST || handler->flags & TIME_SORT) {
		copy_info(node_content, st);
	}
	ft_ptr_vec_pushfront(handler->processed_nodes, node_content);
	++handler->files_num;
}


void get_dir(t_handler* handler, const char* dir_name, t_stat* st) {
	DIR* ptr;
	t_dirent* node_content;
	t_node *dir;

	ptr = opendir(dir_name);

	///init and copy name; here will come readlinked dir name
	dir = init_node("", dir_name, st_mode2d_type(st->st_mode));
	///copy st needed fields
	copy_info(dir, st);
	while ((node_content = readdir(ptr)) != NULL) {
		if (!(handler->flags & ALL_NODES) && node_content->d_name[0] == '.')
			continue ;
		ft_ptr_vec_pushback(dir->nodes, init_node(dir->d_name,
											      node_content->d_name,
											      node_content->d_type));

		///get additional info
		if (handler->flags & LIST || handler->flags & TIME_SORT) {
			///stat work only with full paths
			if (!CURRENT_NODE->full_path_is_set)
				set_fullpath(CURRENT_NODE, dir->d_name, node_content->d_name);
			get_node_info(CURRENT_NODE);
			dir->total += CURRENT_NODE->st_blocks;
		}
		///DO NOT TAKE '.' OR '..'!!!
		if ((handler->flags & RECURSIVE) &&
				 ft_strcmp(node_content->d_name, "..") &&
				 ft_strcmp(node_content->d_name, ".") &&
				 CURRENT_NODE->d_type == DT_DIR) {
			if (!CURRENT_NODE->full_path_is_set)
				set_fullpath(CURRENT_NODE, dir->d_name, node_content->d_name);
			ft_ptr_vec_pushback(handler->input_nodes, &CURRENT_NODE->full_path);
		}
	}
	///sort dir ??
	sort_nodes(((t_node**)(dir->nodes->data)), 0,
	  (int)(dir->nodes->length - 1), handler->flags, LOCAL);
	///get filename len
	dir->local_max_filename_len =
			get_max_filename_len(dir->nodes, LOCAL);

	///push processed dir to processed nodes
	ft_ptr_vec_pushback(handler->processed_nodes, dir);

	closedir(ptr);
}


///difference between dir and file is that in directory (t_node) field node is MALLOCED
///in file it is NULL


///all files are in pushfronted
///all dirs are pushbacked
void read_nodes(t_handler* handler) {
	register size_t i;
	t_stat st;
	char* node_name;

	i = -1;
	///todo: also handle symbolic links WIP
	while (++i < handler->input_nodes->length) {
		///may be use macro instead of creating a variable
		node_name = handler->input_nodes->data[i];
		///R l a t
		/**
		 * if it is a file-> 1 way -> get_file = {readlink{name}, s_nodes* == NULL},
		 * if it is a dir -> 2 way -> get dir = {readlink{name}, s_nodes*, total} -> sort(dir)
		 */
		if (stat(node_name, &st) == -1) {
		 	///should be an error message and continue
		 	error_manager(node_name, CANT_OPEN);
			continue ;

		}
		/**
 		* NOTE: function stat return node type is var st_mode
 		* so we can identify what came to us
 		*/
		 S_ISDIR(st.st_mode) ?
		 	get_dir(handler, node_name, &st) : get_file(handler, node_name, &st);
	}
	///get global namelen max
	handler->global_max_filename_len =
			get_max_filename_len(handler->processed_nodes, GLOBAL);
	//debug_read_nodes(handler, handler->processed_nodes);
}