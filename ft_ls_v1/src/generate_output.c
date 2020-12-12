//
// Created by vera on 04.11.2020.
//

#include "ft_ls.h"

void collect_files(t_cvec *output_str, t_node *node, size_t max, int last_flag)
{
    char    temp[max - node->d_name_len + 1];

    ft_bzero((void *)temp,max - node->d_name_len + 2);
    ft_chr_vec_pushback(output_str, node->d_name);
    if (!last_flag)
        ft_chr_vec_pushback(output_str,(char *)ft_memset((void *)temp, ' ',

                                              max - node->d_name_len + 1));
    else
        ft_chr_vec_pushback(output_str, "\n");
}

void add_to_output(t_cvec *output_str, t_pvec *vec, int *max_list)
{
    int     i;
    char    temp[16];
    t_cvec  *elem;

    i = -1;
    ft_bzero((void *)temp, 16);
    while (vec->length > 0)
    {
        i++;
        elem = (t_cvec *)ft_ptr_vec_popfront(vec);
        if (i % 8 == 2  || i % 8 == 3 || i % 8 == 4 || i % 8 == 5)
        {
            ft_chr_vec_pushback(output_str, (char *)ft_memset((void *)temp, ' ',
                                                              max_list[i % 8] - elem->length + 2));
            ft_bzero(temp, 16);
        }
        else if (i % 8 == 6 || i % 8 == 7)
            ft_chr_vec_pushback(output_str, " ");
        else
            ;
        if (i % 8 != 0)
            ft_chr_vec_pushback(output_str, elem->data);
        if (i % 8 == 0 && i != 0)
            ft_chr_vec_pushback(output_str,"\n");
        if (i % 8 == 0)
        {
            elem->data[1] = '\0';
            ft_chr_vec_pushback(output_str, elem->data);
        }
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
        if (i > 0 && !cond && NODE(processed_nodes, i - 1)->nodes == NULL
        && (handler->flags & LIST))
        {
            add_to_output(handler->output_str, handler->output_vec_util, handler->output_max_list_util);
            ft_chr_vec_pushback(handler->output_str,"\n\n");

        }

        if (processed_nodes->length == 1 && !cond &&
            NODE(processed_nodes, i)->nodes->length == 0) // TODO check empty dir
            continue;
        if (!cond) // Directory
            directory_processing(NODE(processed_nodes, i),handler, processed_nodes->length, i);
        else
            files_processing(NODE(processed_nodes, i), handler, processed_nodes->length, i);

    }
    if ((handler->flags & LIST) && handler->output_str->length == 0)
    {
        add_to_output(handler->output_str, handler->output_vec_util, handler->output_max_list_util); // add new line
        ft_chr_vec_pushback(handler->output_str,"\n");
    }
    write(1, handler->output_str->data, handler->output_str->length);
    //TODO FREE all
}