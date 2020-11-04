//
// Created by professor on 11/4/20.
//

#include "ft_ls.h"

void copy_info(t_node* node, t_stat* st) {
	node->st_mtim = st->st_mtim;
	node->st_size = st->st_size;
	node->st_gid = st->st_gid;
	node->st_uid = st->st_uid;
	node->st_nlink = st->st_nlink;
	node->st_mode = st->st_mode;
	node->st_blocks = st->st_blocks;
	node->st_blksize = st->st_blksize;
}

///may expand
void get_node_info(t_node* node) {
	t_stat st;

	///may be error if -1 is returned
	stat(node->d_name, &st);
	copy_info(node, &st);
}

///may expand
t_node* init_node(const char* node_name, unsigned char d_type) {
	t_node* node;

	if (!(node = ft_memalloc(sizeof(t_node))))
		finish_him();
	ft_memcpy(node->d_name, node_name, MAX_FILENAME_SIZE * sizeof(char));
	node->nodes = ft_ptr_vec_init();
	node->d_type = d_type;
	return node;
}

t_node* init_node_and_get_info(const char* node_name, unsigned char d_type) {
	t_node* node;

	node = init_node(node_name, d_type);
	get_node_info(node);
	return node;
}