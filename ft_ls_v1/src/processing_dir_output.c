//
// Created by vera on 29.11.2020.
//
#include "ft_ls.h"

void    add_dir_name(t_node *node, t_cvec *output_str)
{
    ft_chr_vec_pushback(output_str, node->full_path_is_set ? node->full_path : node->d_name);
    ft_chr_vec_pushback(output_str, ":\n");
}

void    add_total(t_node *node, t_cvec *output_str)
{
    ft_chr_vec_pushback(output_str, "total ");
    ft_chr_vec_pushback(output_str, ft_itoa(node->total));
    ft_chr_vec_pushback(output_str, "\n");
}

void dir_header(t_node *node,t_handler *handler, size_t p_len)
{
    if (p_len != 1 || (node->total > 0 && (handler->flags & LIST)))
        add_dir_name(node, handler->output_str);
    if (node->total > 0 && (handler->flags & LIST))
        add_total(node, handler->output_str);
}

void    directory_processing(t_node *node, t_handler *handler, size_t p_len, size_t i) // processed_nodes->length == p_len
{
    register size_t j;

    dir_header(node, handler, p_len);
    ft_bzero(handler->output_max_list_util, 8); // TODO maybe clear list not here??
    j = -1;
    while (++j < node->nodes->length)
    {
        if (handler->flags & LIST)
            collect_inf(NODE(node->nodes, j), handler->output_vec_util,
                        handler->output_max_list_util);
        else
            collect_files(handler->output_str, NODE(node->nodes, j),
                          node->local_max_filename_len,
                          j == node->nodes->length - 1); // TODO MAX in struct
    }
    if (handler->flags & LIST)
    {
        add_to_output(handler->output_str, handler->output_vec_util,
                      handler->output_max_list_util); //TODO
        if (node->total > 0)
            ft_chr_vec_pushback(handler->output_str, "\n");
    }
    if (i != p_len - 1)
        ft_chr_vec_pushback(handler->output_str, "\n");
}