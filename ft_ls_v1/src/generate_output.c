//
// Created by vera on 04.11.2020.
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
        if (node->name_len > max)
            max = node->name_len;
    }
    return (max);
}

void collect_files(t_cvec *output_str, t_node *node, size_t max, int last_flag)
{
    void    *temp;

    ft_chr_vec_pushback(output_str, node->d_name);
    temp = ft_strnew(max - node->name_len + 1); // TODO how did not use malloc? or use malloc once
    if (!last_flag)
        ft_chr_vec_pushback(output_str,(char *)ft_memset(temp, ' ',
                                              max - node->name_len + 1));
    else
        ft_chr_vec_pushback(output_str, "\n");
    ft_memdel(&temp);
}

void    collect_inf(t_cvec *output_str, t_node *node)
{
    // create buffer for one line and manage string into buffer
    t_stat st;
    size_t max;

    stat(node->d_name, &st);
    ft_printf("%c%s %s %s %s %s %s %s\n", print_type(node->d_type),
              print_permissions(st.st_mode),
              ft_itoa(st.st_nlink),
              getpwuid(st.st_uid)->pw_name,
              getgrgid(st.st_gid)->gr_name,
              ft_itoa(st.st_size),
              print_time(&st.st_mtim.tv_sec),
              node->d_name);
    ft_chr_vec_pushback(output_str, print_type(node->d_type));
    ft_chr_vec_pushback(output_str, print_permissions(st.st_mode));
    ft_chr_vec_pushback(output_str, ft_itoa(st.st_nlink));
    ft_chr_vec_pushback(output_str, getpwuid(st.st_uid)->pw_name);
    ft_chr_vec_pushback(output_str, getgrgid(st.st_gid)->gr_name);
    ft_chr_vec_pushback(output_str, ft_itoa(st.st_size));
    ft_chr_vec_pushback(output_str, print_time(&st.st_mtim.tv_sec));
    ft_chr_vec_pushback(output_str, node->d_name);


}

void output_manager(t_handler *handler, t_pvec *processed_nodes)  //TODO Not support Recursive flag
{
    // Check flags
    // Check type
    // Processing empty directory
    // First files second directory with files
    // For directory print total
    register    size_t i;
    register    size_t j;
    t_cvec      *output_str;
    size_t      max;
    int         cond;

    i = -1;
    output_str = ft_chr_vec_init(1000); // len names of files + white space
    if (handler->flags & LIST)
    {
        while (++i < processed_nodes->length)
        {
            cond = NODE(processed_nodes, i)->nodes == NULL;
            if (processed_nodes->length == 1 && !cond &&
                NODE(processed_nodes, i)->nodes->length == 0) // TODO check empty dir
                continue;
            if (!cond) // Directory
                ;
            else
            {
                collect_inf(output_str, NODE(processed_nodes, i));
            }
        }
    }
    else
    {
        while (++i < processed_nodes->length) // Total directories processed
        {
            cond = NODE(processed_nodes, i)->nodes == NULL;
            if (processed_nodes->length == 1 && !cond &&
            NODE(processed_nodes, i)->nodes->length == 0) // TODO check empty dir
                continue;
            if (!cond) // Directory
            {
                // TODO conditions
                if (processed_nodes->length != 1)
                {
                    ft_chr_vec_pushback(output_str,
                                        NODE(processed_nodes, i)->full_path_is_set ?
                                        NODE(processed_nodes, i)->full_path : NODE(processed_nodes, i)->d_name);
                    ft_chr_vec_pushback(output_str, ":\n");
                }
                // cycle by files in directory
                j = -1;
                while (++j < NODE(processed_nodes, i)->nodes->length)
                {
                    max = find_max((t_pvec *)NODE(processed_nodes, i)->nodes); // TODO next version
                    collect_files(output_str, NODE(NODE(processed_nodes, i)->nodes, j), max,
                                  j == NODE(processed_nodes, i)->nodes->length - 1);
                }
                if (i != processed_nodes->length - 1)
                    ft_chr_vec_pushback(output_str, "\n");
            }
            else
            {
                max = find_max(processed_nodes); // TODO next version
                collect_files(output_str, NODE(processed_nodes, i), max,
                              (i <= processed_nodes->length - 2 &&
                              (NODE(processed_nodes, i + 1)->nodes != NULL)) ||
                                          i == processed_nodes->length - 1);
                if (i <= processed_nodes->length - 2 && (NODE(processed_nodes, i + 1)->nodes != NULL))
                    ft_chr_vec_pushback(output_str, "\n");
            }
        }
    }
    ft_printf("%s", output_str->data);
}