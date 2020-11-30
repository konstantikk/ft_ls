//
// Created by professor on 11/8/20.
//

#include "ft_ls.h"

///increasing order
int time_sort_inc(const t_node* lhs, const t_node* rhs) {
	return lhs->st_mtim.tv_sec > rhs->st_mtim.tv_sec;
}

///decreasing order order
int time_sort_dec(const t_node* lhs, const t_node* rhs) {
	return lhs->st_mtim.tv_sec < rhs->st_mtim.tv_sec;
}

///increasing order
int local_name_sort_inc(const t_node* lhs, const t_node* rhs) {
	return ft_strcmp((const char *) &lhs->d_name, (const char*)&rhs->d_name) < 0;
}

///decreasing order
int local_name_sort_dec(const t_node* lhs, const t_node* rhs) {
	return ft_strcmp((const char *) &lhs->d_name, (const char*)&rhs->d_name) > 0;
}

///increasing order
int global_name_sort_inc(const t_node* lhs, const t_node* rhs) {
	if (lhs->full_path_is_set && rhs->full_path_is_set) {
		return ft_strcmp((const char *) &lhs->full_path, (const char*)&rhs->full_path) < 0;
	} else if (lhs->full_path_is_set) {
		return ft_strcmp((const char *) &lhs->full_path, (const char*)&rhs->d_name) < 0;
	} else if (rhs->full_path_is_set) {
		return ft_strcmp((const char *) &lhs->d_name, (const char*)&rhs->full_path) < 0;
	} else {
		return ft_strcmp((const char *) &lhs->d_name, (const char*)&rhs->d_name) < 0;
	}
}

///decreasing order
int global_name_sort_dec(const t_node* lhs, const t_node* rhs) {
	if (lhs->full_path_is_set && rhs->full_path_is_set) {
		return ft_strcmp((const char *) &lhs->full_path, (const char*)&rhs->full_path) > 0;
	} else if (lhs->full_path_is_set) {
		return ft_strcmp((const char *) &lhs->full_path, (const char*)&rhs->d_name) > 0;
	} else if (rhs->full_path_is_set) {
		return ft_strcmp((const char *) &lhs->d_name, (const char*)&rhs->full_path) > 0;
	} else {
		return ft_strcmp((const char *) &lhs->d_name, (const char*)&rhs->d_name) > 0;
	}
}

///if happens name sort in the end
///directories will be sort by full path
///files will be sorted by d_name

void node_swap(t_node** lhs, t_node** rhs) {
	t_node* temp;

	temp = *lhs;
	*lhs = *rhs;
	*rhs = temp;
}

int partition(t_node** nodes, const int begin, const int end, int (*cond)(const t_node*, const t_node*)) {
	register int pivot;
	register int i;
	register int j;

	pivot = end;
	i = begin - 1;
	j = begin;
	while (j < end) {
		if (cond(nodes[j], nodes[pivot]))
			node_swap(&nodes[++i], &nodes[j]);
		++j;
	}
	node_swap(&nodes[i + 1], &nodes[pivot]);
	return i + 1;
}

void quicksort(t_node** nodes, const int begin, const int end, int (*cond)(const t_node*, const t_node*)) {
	int part;

	if (begin < end) {
		part = partition(nodes, begin, end, cond);

		quicksort(nodes, begin, part - 1, cond);
		quicksort(nodes, part + 1 , end, cond);
	}
}

///function driver which will decide what kind of sort we need
void sort_nodes(t_node** nodes,
		  const int begin, const int end, const unsigned int flags, const t_exec sort_type) {
	if (begin >= end)
		return ;
	///ifs for specific sort and else is for default name sort
	if (flags & TIME_SORT) {
		quicksort(nodes, begin, end,
			  flags & REVERSE_SORT ? time_sort_dec : time_sort_inc);
	}
	/**
	 	if no specific sort is selected we will sort by name
		it gets a little bit tricky here
		if this function is invoked in the LOCAL directory sort
		it will use d_names as values to compare
		if this function is invoked in the GLOBAL sort
		it will use fullpath names firsthand and if they are not defined than it will use d_name
	 **/
	else {
		if (sort_type == LOCAL)
			quicksort(nodes, begin, end,
				  flags & REVERSE_SORT ? local_name_sort_dec : local_name_sort_inc);
		else if (sort_type == GLOBAL)
			quicksort(nodes, begin, end,
			 	  flags & REVERSE_SORT ? global_name_sort_dec : global_name_sort_inc);
	}

}
