//
// Created by professor on 10/31/20.
//
#include "ft_ls.h"

void debug_output_content_one(t_node* node) {
	printf("{\n\tt_dirent part:\n");
	printf("\tfull_path: %s\n", node->full_path);
	printf("\td_name: %s\n}", node->d_name);
	printf("{\n\tt_stat part:\n");
	printf("\tst_mode: %d\n", node->st_mode);
	printf("\tst_nlink: %lu\n", node->st_nlink);
	printf("\tst_uid: %d\n", node->st_uid);
	printf("\tst_gid: %d\n", node->st_gid);
	printf("\tst_size: %lu\n", node->st_size);
	printf("\tst_blksize: %lu\n", node->st_blksize);
	printf("\tst_blocks: %lu\n", node->st_blocks);
	printf("\ttotal: %lu\n", node->total);
	printf("\tst_mtim.tv_sec: %lu\n}\n", node->st_mtim.tv_sec);
	printf("}\n\n");
}

void debug_read_nodes(t_handler* handler, t_pvec* processed_nodes) {
	printf("total directories processed: %lu\n", processed_nodes->length);
	for (int i = 0; i < processed_nodes->length; ++i) {
		int cond = NODE(processed_nodes, i)->nodes == NULL;
		printf("%s\n", cond ? "FILE" : "DIR");
		debug_output_content_one(NODE(processed_nodes, i));
		if (!cond) {
			printf("CONTENT\n");
			printf("total nodes in dir: %lu\n", NODE(processed_nodes, i)->nodes->length);
			for (int j = 0; j < NODE(processed_nodes, i)->nodes->length; ++j) {
				debug_output_content_one(NODE(NODE(processed_nodes, i)->nodes, j));
			}
		}
		printf("\n\n");
	}
}
/**
 * issues we are facing:
 *  	1) output name of the directory that we are parsing then the content of it
 *  	2) path creation should be rewritten
 *  	3) 1 node -> no name in header, name in header - need to implement
 *  	4) correct error management
 *  	5) total must be divided by 2
 *  	WIP
 */

///
void set_fullpath(t_node* node, const char* prefix, const char* node_name) {
	const size_t len_prefix = ft_strlen(prefix);
	const size_t len_node_name = ft_strlen(node_name);

	///strnew creates len + 1 elem for '\0'
	///we need additional symbol for '/' thats why we pass to strnew +1
	ft_memcpy(node->full_path, prefix, len_prefix * sizeof(char));
	///put slash
	node->full_path[len_prefix] = '/';
	///copy rest
	///because we dont want to override new symbol '\' which is placed at the position len_prefix + 1
	ft_memcpy(node->full_path + (len_prefix + 1), node_name, len_node_name * sizeof(char));
	///set bool variable that full path is set for easy access
	node->full_path_is_set = 1;
}

void get_file(t_handler* handler, const char* file_name, t_stat* st) {
	t_node* node_content;

	if (!(handler->flags & ALL_NODES) && file_name[0] == '.')
		return ;
	///in files which came as args the type is in st
	node_content = init_node(file_name, S_ISLNK(st->st_mode) ? DT_LNK : 0);

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
	if (ptr == NULL)
		finish_him();


	///init and copy name; here will come readlinked dir name
	dir = init_node(dir_name, S_ISDIR(st->st_mode) ? DT_DIR : DT_LNK);
	///copy st needed fields
	copy_info(dir, st);
	while ((node_content = readdir(ptr)) != NULL) {
		if (!(handler->flags & ALL_NODES) && node_content->d_name[0] == '.')
			continue ;
		ft_ptr_vec_pushback(dir->nodes, init_node(node_content->d_name, node_content->d_type));

		///get additional info
		if (handler->flags & LIST || handler->flags & TIME_SORT) {
			///stat work only with full paths
			set_fullpath(CURRENT_NODE, dir->d_name, node_content->d_name);
			get_node_info(CURRENT_NODE);
			dir->total += CURRENT_NODE->st_blocks;
		}
		///DO NOT TAKE '.' OR '..'!!!
		if ((handler->flags & RECURSIVE) &&
				 ft_strcmp(node_content->d_name, "..") &&
				 ft_strcmp(node_content->d_name, ".") &&
		(CURRENT_NODE->d_type == DT_LNK || CURRENT_NODE->d_type == DT_DIR)) {
			if (!CURRENT_NODE->full_path_is_set)
				set_fullpath(CURRENT_NODE, dir->d_name, node_content->d_name);
			ft_ptr_vec_pushback(handler->input_nodes, &CURRENT_NODE->full_path);
		}
	}
	///sort dir ??
	sort_nodes(((t_node**)(dir->nodes->data)), 0,
	  (int)(dir->nodes->length - 1), handler->flags);
	///push processed dir to processed nodes
	ft_ptr_vec_pushback(handler->processed_nodes, dir);
	if (closedir(ptr) == -1)
		finish_him();
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
		 	///need to work this out correctly if we have multiple inputs
		 	/// it WONT stop if one of the nodes doesnt exist
		 	finish_him();
		}
		/**
 		* NOTE: function stat return node type is var st_mode
 		* so we can identify what came to us
 		*/
		 S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode) ?
		 	get_dir(handler, node_name, &st) : get_file(handler, node_name, &st);
	}

	//debug_read_nodes(handler, handler->processed_nodes);
}