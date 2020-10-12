//
// Created by professor on 10/9/20.
//

#include "ft_ls.h"

void finish_him() {
	perror(strerror(errno));
	exit(-1);
}

///in case of an error we need to free the whole struct so we will take it as a parameter
///or maybe we could make it global??
///we will probably need to save the names of directories not the ptrs to them (!!!(fixed))

void dir_push_wrapper(t_handler* handler, const char* dir_name)
/*
 * push struct t_dir to main struct t_handler
 *
 */
{
    t_dir *dir_holder;

    if ((dir_holder = (t_dir *)ft_memalloc(sizeof(t_dir))) == NULL)
        finish_him(); // TODO free struct
    if ((dir_holder->dir_name = ft_strdup(dir_name)) == NULL)
        finish_him(); // TODO
	if (ft_ptr_vec_pushback(handler->dir_vec, (void*)dir_holder) == -1)
		///freshers
		finish_him();
}

///init here more field if needed
///may be takes 4 args size of dirs, dirs, and flags for execution and for the function


t_handler* init_handler(const int size, const char** dirs, const t_exec exec)
{
	t_handler* handler;
	register int i;

	if ((handler = (t_handler*)ft_memalloc(sizeof(t_handler))) == NULL)
		finish_him();

	if ((handler->dir_vec = ft_ptr_vec_init()) == NULL)
	{
		ft_memdel((void**)&handler);
		finish_him();
	}
	i = 1;
	if (exec == DIRS_IN_ARGS)
		while (i < size)
		{
			dir_push_wrapper(handler, dirs[i]);
			++i;
		}
	else if (exec == NO_DIRS_IN_ARGS)
		dir_push_wrapper(handler, CURRENT_DIR);

	return handler;
}

///flags will work here
///this function needs to be well thought out

///opening and closing of dir is happening here
void output_content(t_handler* handler, const char* dir_name, const int dirs_size)
{
	DIR* dir_ptr = opendir(dir_name);

	if (dir_ptr == NULL)
		finish_him();
	if (dirs_size > 1)
		ft_printf("%s:\n", dir_name);
	t_dirent* dir_data;
	while ((dir_data = readdir(dir_ptr)) != NULL)
		///bad output
		ft_printf("%s ", dir_data->d_name);
	ft_putchar('\n');
	if (closedir(dir_ptr) == -1)
		finish_him();
}

void read_dirs(t_handler* handler)
{
	register int i;

	i = 0;
	///slightly better
	while (i < handler->dir_vec->length)
	{
		output_content(handler, handler->dir_vec->data[i], handler->dir_vec->length);
		++i;
	}
}

int is_dir(char *dir_name)
/*
 * check directory this object or not
 * in case of true return 1 otherwise 0
 */
{
    return (1);
}

char *folder_processing(t_handler *handler, t_dir *dir) // recursive flag, t/l/
/*
 * read directory,
 * local sorting file in directory, formatting output and save in dir->output_line
 */
{
    char *output_line;

    if (is_dir(dir->dir_name))
        ;
        // collect all files and dirs in folder + formatting
        // sorting by key
        // output_line
    else
        ;//output_line =  function formating str


    return (output_line);
}

void ft_ls(t_handler *handler)
/*
 * main circle on directories, with recursive flag new directories added to the end
 */
{
    int     i;

    i = -1;
    while (++i < (int)handler->dir_vec->length)
    {
        folder_processing()
    }
    // sort directory in dir_vec by key, check flag -r -t ...

    //output cycle on vector and fill t_cvec *final_output ?

    // write(final_output)

    // free memory
}

int main(int argc, char** argv)
{
	t_handler* handler;

	///here will be happening parsing of args and dirs
	///but before flags we will be relying on argc as a counter of dirs

	///parse_args(argc, argv);

	///argv will be changed for array of actual dir names
	handler = init_handler(argc, (const char**)argv,
						argc == 1 ? NO_DIRS_IN_ARGS : DIRS_IN_ARGS);

	for (int i=0; i < handler->dir_vec->length; i++)
    {
	    printf("%s \n", ((t_dir*)(handler->dir_vec->data[i]))->dir_name);
    }

    //read_dirs(handler);

	///display_content();
	///free_data();

	return (0);
}
