//
// Created by vera on 04.11.2020.
//

#include "ft_ls.h"

void collect_files(t_cvec *output_str, t_node *node, size_t max, int last_flag)
{
    void    *temp;

    ft_chr_vec_pushback(output_str, node->d_name);
    temp = ft_strnew(max - node->d_name_len + 1); // TODO how did not use malloc? or use malloc once []
    if (!last_flag)
        ft_chr_vec_pushback(output_str,(char *)ft_memset(temp, ' ',
                                              max - node->d_name_len + 1));
    else
        ft_chr_vec_pushback(output_str, "\n");
    ft_memdel(&temp);
}

void add_to_output(t_cvec *output_str, t_pvec *vec, int *max_list)
{
    int     i;
    void    *temp;

    i = -1;
    temp = ft_strnew(16); // TODO no malloc []
    while (++i < vec->length)
    {
        if (i % 8 == 2  || i % 8 == 3 || i % 8 == 4 || i % 8 == 5)
        {
            ft_chr_vec_pushback(output_str, (char *)ft_memset(temp, ' ',
                                                              max_list[i % 8] - ((t_cvec *)(vec->data)[i])->length + 2));
            ft_bzero(temp, 16);
        }
        else if (i % 8 == 6 || i % 8 == 7)
            ft_chr_vec_pushback(output_str, " ");
        else
            ;
        if (i % 8 != 0)
            ft_chr_vec_pushback(output_str, ((t_cvec *)(vec->data)[i])->data);
        if (i % 8 == 0 && i != 0)
            ft_chr_vec_pushback(output_str,"\n");
    }
    //ft_chr_vec_pushback(output_str,"\n");
}

void output_manager(t_handler *handler, t_pvec *processed_nodes)
{
    register    size_t i;
    int         cond;

    handler->output_max_list_util = (int *)ft_memalloc(8 * sizeof(int));
    handler->output_vec_util = ft_ptr_vec_init();
    handler->output_str = ft_chr_vec_init(1000);
    i = -1;
    while (++i < processed_nodes->length)
    {
        cond = NODE(processed_nodes, i)->nodes == NULL;
        if (processed_nodes->length == 1 && !cond &&
            NODE(processed_nodes, i)->nodes->length == 0) // TODO check empty dir
            continue;
        if (!cond) // Directory
            directory_processing(NODE(processed_nodes, i),handler, processed_nodes->length, i);
        else
            files_processing(NODE(processed_nodes, i), handler, processed_nodes->length, i);
    }
    write(1, handler->output_str->data, handler->output_str->length);
    //TODO FREE all
    //ft_printf("%s", output_str->data);
}