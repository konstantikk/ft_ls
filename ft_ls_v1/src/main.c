//
// Created by professor on 10/9/20.
//

#include "ft_ls.h"

void finish_him() {
	perror("ls: ");
	exit(-1);
}

///in case of an error we need to free the whole struct so we will take it as a parameter
///or maybe we could make it global??
///we will probably need to save the names of directories not the ptrs to them (!!!(fixed))


t_handler* init_handler(void) {
	t_handler* handler;

	if ((handler = (t_handler*)ft_memalloc(sizeof(t_handler))) == NULL)
		finish_him();

	if ((handler->input_nodes = ft_ptr_vec_init()) == NULL) {
		ft_memdel((void**)&handler);
		finish_him();
	}
	if ((handler->processed_nodes = ft_ptr_vec_init()) == NULL) {
		ft_ptr_vec_del(&handler->input_nodes, ft_memdel);
		ft_memdel((void**)&handler);
		finish_him();
	}
	return handler;
}

void sort_all_nodes(t_handler* handler) {
	sort_nodes(handler->processed_nodes->data,
			0, handler->files_num - 1, handler->flags, GLOBAL);
	sort_nodes(handler->processed_nodes->data,
			   handler->files_num, handler->processed_nodes->length - 1, handler->flags, GLOBAL);
}

int main(int argc, char** argv) {
	t_handler* handler;

	///here will be happening parsing of args and dirs
	///but before flags we will be relying on argc as a counter of dirs


	///argv will be changed for array of actual dir names
	handler = init_handler();
	parse_input(argc, argv, handler);
	read_nodes(handler);
	sort_all_nodes(handler);
	output_manager(handler, handler->processed_nodes);
	///free_data();

	return (0);
}
