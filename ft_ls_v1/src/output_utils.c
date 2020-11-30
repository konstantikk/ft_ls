//
// Created by vera on 29.11.2020.
//
#include "ft_ls.h"

int find_max(t_pvec * nodes) // TODO useless in next versions
{
    t_node  *node;
    size_t     max;

    max = 0;
    for (int i=0; i < nodes->length; i++)
    {
        node = (t_node *) (nodes->data[i]);
        if (node->d_name_len > max)
            max = node->d_name_len;
    }
    return (max);
}

void    init_list(t_pvec *vec, char *res, int *max)
{
    t_cvec *temp;

    temp = ft_chr_vec_init(20);
    ft_chr_vec_pushback(temp, res);
    ft_ptr_vec_pushback(vec, (void *)temp);
    if (*max < temp->length)
        *max = temp->length;
}

void    collect_inf(t_node *node, t_pvec *vec, int *max)
{
    //t_stat  st;
    char    c;

    //stat(node->full_path_is_set ? node->full_path : node->d_name, &st); // deprecated
    c = print_type(node->d_type); // st_mode
    init_list(vec, (char *)&c, &(max[0]));
    init_list(vec, print_permissions(node->st_mode), &(max[1]));
    init_list(vec, ft_itoa(node->st_nlink), &(max[2]));
    init_list(vec, getpwuid(node->st_uid)->pw_name, &(max[3]));
    init_list(vec, getgrgid(node->st_gid)->gr_name, &(max[4]));
    init_list(vec, ft_itoa(node->st_size), &(max[5]));
    init_list(vec, print_time(&(node->st_mtim.tv_sec)), &(max[6]));
    init_list(vec, node->d_name, &(max[7]));
}