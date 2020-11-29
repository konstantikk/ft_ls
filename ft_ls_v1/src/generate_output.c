//
// Created by vera on 04.11.2020.
//

#include "ft_ls.h"

int find_max(t_handler * handler)
{
    t_node  *node;
    size_t     max;

    max = 0;
    for (int i=0; i < handler->processed_nodes->length; i++)
    {
        node = (t_node *) (handler->processed_nodes->data[i]);
        if (node->name_len > max)
            max = node->name_len;
    }
    return (max);
}


void generate_output(t_handler *handler)
{
    t_node *node;
    size_t  max;
    t_cvec *output_str;
    void    *temp;

    output_str = ft_chr_vec_init(10); // len names of files + white space
    max = find_max(handler); // should keep maximum
    for (int i=0; i < handler->processed_nodes->length; i++)
    {
        node = (t_node *)(handler->processed_nodes->data[i]);
        //ft_printf("%s %d\n", node->d_name, max - node->name_len + 1);
        ft_chr_vec_pushback(output_str, node->d_name);
        temp = ft_strnew(max - node->name_len + 1);
        ft_chr_vec_pushback(output_str, (char *)ft_memset(temp, ' ', max - node->name_len + 1));
    }
    ft_printf("%s", output_str->data);
}
char *collect_inf()
{

}

void output_manager(t_handler *handler)  //TODO Not support Recursive flag
{
    // Check flags
    // Check type
    // Processing empty directory
    // First files second directory with files
    // For directory print total
    register    size_t i;
    register    size_t j;
    t_cvec      *output_str;
    t_node      *node;
    size_t      max;
    void        *temp;

    i = -1;
    output_str = ft_chr_vec_init(10); // len names of files + white space
    if (handler->flags & LIST)
    {
        while (++i < handler->processed_nodes->length)
        {

            // collect information find max

        }
    }
    else
    {
        max = handler->global_max->data[handler->global_max->length - 1];//find_max(handler);
        printf("%zu\n max %zu", handler->processed_nodes->length, max);
        while (++i < handler->processed_nodes->length)
        {
            node = (t_node*)(handler->processed_nodes->data[i]);
            if (handler->processed_nodes->length == 1 &&
                node->d_type == DT_DIR && node->nodes->length == 0) // TODO check empty dir
                continue;
            if (node->d_type == DT_DIR)
            {
                ft_chr_vec_pushback(output_str, ft_strjoin(node->d_name, ft_strdup(":\n"))); // dir_name:\n
                // cycle by files in directory
                j = -1;
                while (++j < node->nodes->length)
                {

                }
                ft_chr_vec_pushback(output_str, "\n");
            }
            else
            {
                ft_chr_vec_pushback(output_str, node->d_name);
                temp = ft_strnew(max - node->name_len + 1);
                if (i != handler->processed_nodes->length - 1)
                    ft_chr_vec_pushback(output_str, (char *)ft_memset(temp, ' ', max - node->name_len + 1));
            }
        }
    }
    ft_printf("%s", output_str->data);
}