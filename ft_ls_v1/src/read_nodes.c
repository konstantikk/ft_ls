//
// Created by professor on 10/31/20.
//
#include "ft_ls.h"

///may expand
t_node* create_node(const t_dirent* node_content) {
	t_node* node;

	if (!(node = ft_memalloc(sizeof(t_node))))
		finish_him();
	ft_memcpy(node->d_name, node_content->d_name, 256 * sizeof(char));
	node->d_type = node_content->d_type;
	return node;
}

///may expand
void get_additional_info(t_node* node) {
	t_stat st;
	stat(node->d_name, &st);
	node->st_mtim = st.st_mtim;
	node->st_size = st.st_size;
	node->st_gid = st.st_gid;
	node->st_uid = st.st_uid;
	node->st_nlink = st.st_nlink;
	node->st_mode = st.st_mode;
}

void debug_read_nodes(t_handler* handler, t_pvec* processed_nodes) {
	printf("total directories processed: %lu\n", processed_nodes->length);
	for (int i = 0; i < processed_nodes->length; ++i) {
		printf("{\n\tt_dirent part:\n");
		printf("\td_name: %s\n", ((t_node*)processed_nodes->data[i])->d_name);
		printf("\td_type: %d\n", ((t_node*)processed_nodes->data[i])->d_type);
		if (handler->flags & LIST || handler->flags & TIME_SORT) {
			printf("{\n\tt_stat part:\n");
			printf("\tst_mode: %d\n", ((t_node*)processed_nodes->data[i])->st_mode);
			printf("\tst_nlink: %lu\n", ((t_node*)processed_nodes->data[i])->st_nlink);
			printf("\tst_uid: %d\n", ((t_node*)processed_nodes->data[i])->st_uid);
			printf("\tst_gid: %d\n", ((t_node*)processed_nodes->data[i])->st_gid);
			printf("\tst_size: %lu\n", ((t_node*)processed_nodes->data[i])->st_size);
			printf("\tst_mtim.tv_sec: %lu\n}\n", ((t_node*)processed_nodes->data[i])->st_mtim.tv_sec);
		}
		printf("}\n\n");
	}
}
/**
 * issues we are facing:
 *  	1) output name of the directory that we are parsing then the content of it
 *  	2) path creation should be rewritten
 *  	WIP
 */

void read_nodes(t_handler* handler) {
	register size_t i;
	DIR* ptr;
	t_dirent* node_content;

	i = 0;
	///todo: also handle symbolic links
	while (i < handler->input_nodes->length) {
		///R l a t
		ptr = opendir(handler->input_nodes->data[i]);
		if (ptr == NULL)
			finish_him();
		while ((node_content = readdir(ptr)) != NULL) {
			///skip hidden if needed
			if (!(handler->flags & ALL_NODES) && node_content->d_name[0] == '.')
				continue ;
			ft_ptr_vec_pushback(handler->processed_nodes, create_node(node_content));
			///get additional info
			if (handler->flags & LIST || handler->flags & TIME_SORT) {
				///get stat
				get_additional_info(CURRENT_NODE);
			}
			///DO NOT TAKE '.' OR '..'!!!
			else if ((handler->flags & RECURSIVE) &&
			 		 ft_strcmp(node_content->d_name, "..") &&
			 		 ft_strcmp(node_content->d_name, ".") &&
					(node_content->d_type == DT_DIR || node_content->d_type == DT_LNK)) {
				///if new struct is a dir push it to the end of the list of input_nodes
				///may be append ancestor dir in the path
				///very ugly way of doing it, needs refactor
				char path[256];
				size_t len = ft_strlen(handler->input_nodes->data[i]);
				ft_memcpy(path, handler->input_nodes->data[i], len);
				path[len] = '/';
				path[len + 1] = '\0';
				ft_ptr_vec_pushback(handler->input_nodes, ft_strjoin(path, node_content->d_name));
			}
		}
		if (closedir(ptr) == -1)
			finish_him();
		++i;
	}
	debug_read_nodes(handler, handler->processed_nodes);
}