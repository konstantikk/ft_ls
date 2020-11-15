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

void sort_all_nodes(t_handler* handler) {
	sort_nodes(handler->processed_nodes->data,
			0, handler->files_num - 1, handler->flags);
	///sort dirs right now sort is happening by d_name FIXME
	sort_nodes(handler->processed_nodes->data,
			   handler->files_num, handler->processed_nodes->length - 1, handler->flags);
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
	//debug_read_nodes(handler, handler->processed_nodes);
	///sort files
	///display_content();
	///free_data();
	output_manager(handler, handler->processed_nodes);

	return (0);
}
