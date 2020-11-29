//
// Created by vera on 29.11.2020.
//
#include "ft_ls.h"

void files_processing(t_node *node, t_handler *handler, size_t p_len, size_t i)
{
    t_cvec *out;

    out = handler->output_str;
    if (handler->flags & LIST)
    {
        collect_inf(node, handler->output_vec_util, handler->output_max_list_util);
        add_to_output(out, handler->output_vec_util, handler->output_max_list_util);
        return;
    }
    if (p_len != 1)
    {
        collect_files(out, node, find_max(handler->processed_nodes),
                     (i <= p_len - 2 &&
                     (NODE(handler->processed_nodes, i + 1)->nodes != NULL))
                     || i == p_len - 1);
        if (i <= p_len - 2 && (NODE(handler->processed_nodes, i + 1)->nodes != NULL))
            ft_chr_vec_pushback(out, "\n");
    }
    else
    {
        ft_chr_vec_pushback(out, node->d_name);
        ft_chr_vec_pushback(out, "\n");
    }
}