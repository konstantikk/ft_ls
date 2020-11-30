//
// Created by professor on 11/15/20.
//
#include "ft_ls.h"

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

	node->full_path_len = ft_strlen(node->full_path); ///full_path len

	node->full_path_is_set = 1;
}


/**
 * we've got names in two forms: local and global
 * if we want to know the longest name in local directory we compare d_names
 * if we want to know the longest global name we will compare full_paths is they are defined
 * else we will compare d_names as well
 */

void local_max(const t_node* lhs, size_t* rhs) {
	if (*rhs < lhs->d_name_len)
		*rhs = lhs->d_name_len;
}

void global_max(const t_node* lhs, size_t* rhs) {
	if (lhs->full_path_is_set && *rhs < lhs->full_path_len) {
		*rhs = lhs->full_path_len;
	} else if (*rhs < lhs->d_name_len) {
		*rhs = lhs->d_name_len;
	}
}

static size_t get_max(t_node** nodes, size_t len,  void (*cond)(const t_node*, size_t*))  {
	register int i;
	size_t max_len;

	i = 0;
	max_len = 0;
	while(i < len) {
		cond(nodes[i], &max_len);
		++i;
	}
	return max_len;
}

size_t get_max_filename_len(t_pvec* nodes,  const t_exec max_type) {
	register size_t max_len;

	max_len = 0;
	if (max_type == LOCAL) {
		max_len = get_max(nodes->data, nodes->length, local_max);
	} else if (max_type == GLOBAL) {
		max_len = get_max(nodes->data, nodes->length, global_max);
	}
	return max_len;
}

///debug

static void debug_output_content_one(t_node* node) {
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
	printf("{\n\tlocal_max_filename_len: %lu\n", node->local_max_filename_len);
	printf("\td_name_len: %lu\n", node->d_name_len);
	printf("\tfull_path_len: %lu\n}\n", node->full_path_len);
	printf("}\n\n");
}

void debug_read_nodes(t_handler* handler, t_pvec* processed_nodes) {
	printf("total directories processed: %lu\n", processed_nodes->length);
	printf("longest filename is: %lu\n", handler->global_max_filename_len);
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