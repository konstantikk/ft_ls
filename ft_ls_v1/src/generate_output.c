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
        if (node->d_name_len > max)
            max = node->d_name_len;
    }
    ft_printf("MAX CHECK found: %d kolya: %d\n", max, node->local_max_filename_len);
    return (max);
}


void collect_files(t_cvec *output_str, t_node *node, size_t max, int last_flag)
{
    void    *temp;

    ft_chr_vec_pushback(output_str, node->d_name);
    temp = ft_strnew(max - node->d_name_len + 1); // TODO how did not use malloc? or use malloc once
    if (!last_flag)
        ft_chr_vec_pushback(output_str,(char *)ft_memset(temp, ' ',
                                              max - node->d_name_len + 1));
    else
        ft_chr_vec_pushback(output_str, "\n");
    ft_memdel(&temp);
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
    t_stat  st;
    char    c;

    stat(node->full_path_is_set ? node->full_path : node->d_name, &st);
    c = print_type(node->d_type);
    init_list(vec, (char *)&c, &(max[0]));
    init_list(vec, print_permissions(st.st_mode), &(max[1]));
    init_list(vec, ft_itoa(st.st_nlink), &(max[2]));
    init_list(vec, getpwuid(st.st_uid)->pw_name, &(max[3]));
    init_list(vec, getgrgid(st.st_gid)->gr_name, &(max[4]));
    init_list(vec, ft_itoa(st.st_size), &(max[5]));
    init_list(vec, print_time(&st.st_mtim.tv_sec), &(max[6]));
    init_list(vec, node->d_name, &(max[7]));
}

void add_to_output(t_cvec *output_str, t_pvec *vec, int *max_list)
{
    int     i;
    void    *temp;

    i = -1;
    temp = ft_strnew(16);
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
    int      *max_list;
    int         max;

    int         cond;
    t_pvec      *vec; // add to struct

    max_list = (int *)ft_memalloc(8 * sizeof(int));
    vec = ft_ptr_vec_init();
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
            {// total
                if (processed_nodes->length != 1)
                {
                    ft_chr_vec_pushback(output_str,
                                        NODE(processed_nodes, i)->full_path_is_set ?
                                        NODE(processed_nodes, i)->full_path : NODE(processed_nodes, i)->d_name);
                    ft_chr_vec_pushback(output_str, ":\n");
                    if (NODE(processed_nodes, i)->total > 0)
                    {
                        ft_chr_vec_pushback(output_str, "total ");
                        ft_chr_vec_pushback(output_str, ft_itoa(NODE(processed_nodes, i)->total));
                        ft_chr_vec_pushback(output_str, "\n");
                    }
                }
                j = -1;
                ft_bzero(max_list, 8);
                while (++j < NODE(processed_nodes, i)->nodes->length)
                {
                    collect_inf(NODE(NODE(processed_nodes, i)->nodes, j), vec, max_list);
                }
                add_to_output(output_str, vec, max_list);
                if (NODE(processed_nodes, i)->total > 0)
                    ft_chr_vec_pushback(output_str, "\n");
                if (i != processed_nodes->length - 1)
                    ft_chr_vec_pushback(output_str, "\n");
            }
            else
            {
                collect_inf(NODE(processed_nodes, i), vec, max_list);
                add_to_output(output_str, vec, max_list);
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
                if (processed_nodes->length != 1)
                {
                    max = find_max(processed_nodes); // TODO next version
                    ft_printf("GENERAL MAX: found: %d Kolya: %d\n", max, handler->global_max_filename_len);
                    collect_files(output_str, NODE(processed_nodes, i), max,
                                  (i <= processed_nodes->length - 2 &&
                                   (NODE(processed_nodes, i + 1)->nodes != NULL)) ||
                                  i == processed_nodes->length - 1);
                    if (i <= processed_nodes->length - 2 && (NODE(processed_nodes, i + 1)->nodes != NULL))
                        ft_chr_vec_pushback(output_str, "\n");
                }
                else
                {
                    ft_chr_vec_pushback(output_str, NODE(processed_nodes, i)->d_name);
                    ft_chr_vec_pushback(output_str, "\n");
                }
            }
        }
    }
    ft_printf("%s", output_str->data);
}