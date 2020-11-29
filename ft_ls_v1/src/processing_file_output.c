//
// Created by vera on 29.11.2020.
//
#include "ft_ls.h"

void files_processing(t_node *node, t_handler *handler, size_t p_len, size_t i)
{
    if (handler->flags & LIST)
    {
        collect_inf(node, handler->output_vec_util, handler->output_max_list_util);
       // add_to_output(handler->output_str, handler->output_vec_util, handler->output_max_list_util);
        return;
    }
    if (p_len != 1)
    {
        collect_files(handler->output_str, node, find_max(handler->processed_nodes),
                      (i <= p_len - 2 &&
                       (NODE(handler->processed_nodes, i + 1)->nodes != NULL))
                      || i == p_len - 1);
        if (i <= p_len - 2 && (NODE(handler->processed_nodes, i + 1)->nodes != NULL))
            ft_chr_vec_pushback(handler->output_str, "\n");
    }
    else
    {
        ft_chr_vec_pushback(handler->output_str, node->d_name);
        ft_chr_vec_pushback(handler->output_str, "\n");
    }

}