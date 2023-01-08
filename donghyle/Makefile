NAME			= parser_test
################################# LIBRARIES ####################################
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LINK_LIBFT		= -L$(LIBFT_DIR)
INC_DIR_LIBFT	= -I$(LIBFT_DIR)/includes

LIB_ALL			= $(LIBFT)
LINK_LIBS		= $(LINK_LIBFT)

INC_DIR			= -I. $(INC_DIR_LIBFT) -Iincludes
################################# COMMANDS #####################################
RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP -g
################################ FILENAMES #####################################
FILENAME		= \
				t_node \
				parser/parser \
				parser/parser_util \
				parser/parser_util1 \
				parser/parser_util2 \
				parser/parser_util3 \
				parser/debug/print_nodes \
				envmanager/envmanager \
				envmanager/envmanager_addentry \
				envmanager/envmanager_getval \
				envmanager/envmanager_setval

SRC				= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))
################################# TARGETS ######################################
all:
	@make $(NAME)

$(NAME): $(LIB_ALL) $(OBJ) $(STAT) test_parser.o
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_LIBS) $(LIB_ALL) $(OBJ) test_parser.o -o $@

$(LIBFT):
	@make -s -j4 -C $(LIBFT_DIR)/

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
