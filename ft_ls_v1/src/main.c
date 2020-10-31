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

void dir_push_wrapper(t_handler* handler, const char* dir) {
	if (ft_ptr_vec_pushback(handler->input_nodes, (void*)dir) == -1)
		///freshers
		finish_him();
}

///init here more field if needed
///may be takes 4 args size of dirs, dirs, and flags for execution and for the function


t_handler* init_handler(void) {
	t_handler* handler;

	if ((handler = (t_handler*)ft_memalloc(sizeof(t_handler))) == NULL)
		finish_him();

	if ((handler->input_nodes = ft_ptr_vec_init()) == NULL) {
		ft_memdel((void**)&handler);
		finish_him();
	}
	if ((handler->processed_nodes = ft_ptr_vec_init()) == NULL) {
		ft_memdel((void**)&handler);
		ft_ptr_vec_del(&handler->input_nodes, ft_memdel);
		finish_him();
	}
	return handler;
}

///flags will work here
///this function needs to be well thought out

///opening and closing of dir is happening here
void output_content(t_handler* handler, const char* dir_name, const int dirs_size) {
	DIR* dir_ptr = opendir(dir_name);

	if (dir_ptr == NULL)
		finish_him();
	if (dirs_size > 1)
		ft_printf("%s:\n", dir_name);
	t_dirent* dir_data;
	while ((dir_data = readdir(dir_ptr)) != NULL)
		print_node(dir_data);
	ft_putchar('\n');
	if (closedir(dir_ptr) == -1)
		finish_him();
}

void read_dirs(t_handler* handler) {
	register int i;

	i = 0;
	///slightly better
	while (i < handler->input_nodes->length) {
		output_content(handler, handler->input_nodes->data[i], handler->input_nodes->length);
		++i;
	}
}

int main(int argc, char** argv) {
	t_handler* handler;

	///here will be happening parsing of args and dirs
	///but before flags we will be relying on argc as a counter of dirs


	///argv will be changed for array of actual dir names
	handler = init_handler();
	parse_input(argc, argv, handler);
	read_nodes(handler);
	///sort()

	///display_content();
	///free_data();

	return (0);
}
