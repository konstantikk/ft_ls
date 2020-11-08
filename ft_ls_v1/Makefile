COMPILER = gcc
CHECK_FLAGS = -Wall -Wextra #-Werror
NAME = ft_ls_v1
ADD_SRC = ./src/
RESOURCES = main.c print_nodes.c args_parse.c read_nodes.c node_init.c sort_nodes.c
SRC_S = $(addprefix $(ADD_SRC), $(RESOURCES))
OBJ = $(SRC_S:.c=.o)
ADD_INC = ./includes/
ADD_LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME):  $(OBJ)
	@make  -C ./libft all
	@$(COMPILER) -o $(NAME) $(CHECK_FLAGS) $(COMPILE_FLAGS) $(OBJ) $(ADD_LIBFT)
	@echo ======[Done]======
%.o : %.c
	@echo "$(NAME) >>> Add/Update $<"
	@$(COMPILER) -c -o $@ -I $(ADD_INC) -I ./libft/includes $(CHECK_FLAGS) $<
clean:
	@rm -f $(ADD_SRC)*.o
	@make  -C ./libft clean
fclean: clean
	@rm -f ./$(NAME)
	@make -C ./libft fclean
re: fclean all
