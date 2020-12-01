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
	if (stat(node->full_path, &st) == -1)
		finish_him();
	copy_info(node, &st);
}

///may expand
///readlink should happen in init node
///thats why full path is needed here
t_node* init_node(const char* prefix, const char* node_name, unsigned char d_type) {
	t_node* node;

	if (!(node = ft_memalloc(sizeof(t_node))))
		finish_him();
	node->d_type = d_type;
	ft_memcpy(node->d_name, node_name, MAX_FILENAME_SIZE);
	if (d_type == DT_LNK)
	{
		///if we have a symbolic link d_name will save local link name
		///full_path will save global link name
		///and readlink from global link name will be saved in links_to
		set_fullpath(node, prefix, node_name);
		if (readlink(node->full_path, node->links_to, MAX_FILENAME_SIZE) == -1)
			finish_him();
	}
	if (d_type == DT_DIR) {
		node->nodes = ft_ptr_vec_init();
	}
	node->d_name_len = ft_strlen(node->d_name); ///d_name len
	return node;
}

t_node* init_node_and_get_info(const char* preifx, const char* node_name, unsigned char d_type) {
	t_node* node;

	node = init_node(preifx, node_name, d_type);
	get_node_info(node);
	return node;
}