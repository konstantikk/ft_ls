//
// Created by professor on 11/8/20.
//

#include "ft_ls.h"

///increasing order
int time_sort_inc(const t_node* lhs, const t_node* rhs) {
	return lhs->st_mtim.tv_sec < rhs->st_mtim.tv_sec;
}

///decreasing order order
int time_sort_dec(const t_node* lhs, const t_node* rhs) {
	return lhs->st_mtim.tv_sec > rhs->st_mtim.tv_sec;
}

///increasing order
int name_sort_inc(const t_node* lhs, const t_node* rhs) {
	return ft_strcmp((const char *) &lhs->d_name, (const char*)&rhs->d_name) < 0;
}

///decreasing order
int name_sort_dec(const t_node* lhs, const t_node* rhs) {
	return ft_strcmp((const char *) &lhs->d_name, (const char*)&rhs->d_name) > 0;
}

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

void sort_helper(t_node**nodes, const int begin, const int end,
				 int (*cond)(const t_node*, const t_node*)) {
		quicksort(nodes, begin, end, cond);
}

///function driver which will decide what kind of sort we need
void sort_nodes(t_node** nodes,
		  const int begin, const int end, const unsigned int flags) {

	///ifs for specific sort and else is for default name sort
	if (flags & TIME_SORT) {
		sort_helper(nodes, begin, end,
			  flags & REVERSE_SORT ? time_sort_dec : time_sort_inc);
	} else {
		sort_helper(nodes, begin, end,
			  flags & REVERSE_SORT ? name_sort_dec : name_sort_inc);
	}

}
