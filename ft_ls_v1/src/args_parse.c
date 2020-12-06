//
// Created by professor on 10/25/20.
//

#include "ft_ls.h"

/**
 * this function will take 4 arguments argc, argv, nodes, flags
 * and will fill nodes with files and directories to output and fill flags with options
 * or maybe it will take 3 arguments: argc, argv, main_struct
 *
 * to support: args parse, flags{-l, -r, -R, -a, -t}
 * these tables maps flags to the shift needed for accessing them
*/


static int flag_table_lookup(const char flag) {
	static const char lower_flags[ALPHABET_SIZE] = {
			4, 0, 0, 0, 0, 0, /// -a -b -c -d -e -f
			0, 0, 0, 0, 0, /// -g -h -i -j -k
			1, 0, 0, 0, 0, /// -l -m -n -o -p
			0, 2, 0, 5, 0, /// -q -r -s -t -u
			0, 0, 0, 0, 0 /// -v -w -x -y -z
	};

	static const char upper_flags[ALPHABET_SIZE] = {
			0, 0, 0, 0, 0, 0, /// -A -B -C -D -E -F
			0, 0, 0, 0, 0, /// -G -H -I -J -K
			0, 0, 0, 0, 0, /// -L -M -N -O -P
			0, 3, 0, 0, 0, /// -Q -R -S -T -U
			0, 0, 0, 0, 0 /// -V -W -X -Y -Z
	};
	if (ft_isupper(flag))
		return upper_flags[flag - 'A'];
	else if (ft_islower(flag))
		return lower_flags[flag - 'a'];
	return 0;
}



/**
 * lets assume that people dont name directories with hame of the flags like: -l, -r, -lH
 * warning: standalone '-' IS A NODE
 *
 * original ls assumes than everything what is after '-' is an option
 * so we would build the same parser
 */

static void parse_flags(char* argv, size_t size, t_handler* handler) {
	register int i;
	register unsigned int shift;

	i = 1;
	while (i < size) {
		shift = flag_table_lookup(argv[i]);
		if (shift != 0)
			handler->flags |= (1u << shift);
		else {
			error_manager(&argv[i], NO_OPTION);
			///freeing should be happening
			exit(-1);
		}
		++i;
	}
}

static void debug_parser(t_handler* handler) {
	printf("nodes parsed: {\n");
	for (int i = 0; i < handler->input_nodes->length; ++i) {
		printf("\t%s\n", handler->input_nodes->data[i]);
	}
	printf("total nodes parsed: %lu\n}\n", handler->input_nodes->length);

	printf("flags parsed: {\n");
	int counter = 0;
	unsigned int shift;
	for (int i = 0; i < 26; ++i) {
		shift = flag_table_lookup(i + 'a');
		if (shift != 0 && handler->flags & (1u << shift)) {
			printf("\t-%c with offset: %d\n", i + 'a', shift);
			counter++;
		}
		shift = flag_table_lookup(i + 'A');
		if (shift != 0 && handler->flags & (1u << shift)) {
			printf("\t-%c with offset: %d\n", i + 'A', shift);
			counter++;
		}
	}
	printf("total flags parsed: %d\n}\n", counter);
}

void parse_input(int argc, char** argv, t_handler *handler) {
	register int i;
	size_t size;
	///skip first arg because it is the program name
	i = 1;

	while (i < argc) {
		size = ft_strlen(argv[i]);
		if (argv[i][0] == '-' && size != 1)
			parse_flags(argv[i], size, handler);
		else
			ft_ptr_vec_pushback(handler->input_nodes, argv[i]);
		++i;
	}
	///if we dont have nodes in args
	if (handler->input_nodes->length == 0)
		ft_ptr_vec_pushback(handler->input_nodes, CURRENT_DIR);

	//debug_parser(handler);
}