NAME				= minishell
################################# COMMANDS #####################################
RM					= rm -f
CFLAGS				= -Wall -Werror -Wextra -MMD -MP -g
################################ FILENAMES #####################################
FILENAME			= \
					prompt/minishell

SRC					= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ					= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP					= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))

TEST_FILENAME		= \
					tests/print_nodes \
					tests/print_tokens
TEST_SRC			= $(addsuffix .c, $(TEST_FILENAME))
TEST_OBJ			= $(addsuffix .o, $(TEST_FILENAME))
TEST_DEP			= $(addsuffix .d, $(TEST_FILENAME))
################################# TARGETS ######################################
all:
	@make $(NAME)

include modules.mk

$(NAME): $(LIB_ALL) $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_LIBS) $(LIB_ALL) $(OBJ) $(TEST_OBJ) -o $@

get_n_tok: $(LIB_ALL) $(TEST_OBJ) tests/get_n_tok.o
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_LIBS) $(LIB_ALL) $(TEST_OBJ) tests/get_n_tok.o -o $@

test_parser: $(LIB_ALL) $(TEST_OBJ) tests/test_parser.o
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_LIBS) $(LIB_ALL) $(TEST_OBJ) tests/test_parser.o -o $@

test_envmanager: $(LIB_ALL) $(TEST_OBJ) tests/test_envmanager.o
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_LIBS) $(LIB_ALL) $(TEST_OBJ) tests/test_envmanager.o -o $@

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP) $(TEST_OBJ) $(TEST_DEP)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBLEXER_DIR)
	@make clean -C $(LIBPARSER_DIR)
	@make clean -C $(LIBENVMAN_DIR)
	@make clean -C $(LIBBUILTIN_DIR)
	$(RM) tests/get_n_tok.o tests/get_n_tok.d tests/test_parser.o tests/test_parser.d tests/test_envmanager.o tests/test_envmanager.d

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBLEXER_DIR)
	@make fclean -C $(LIBPARSER_DIR)
	@make fclean -C $(LIBENVMAN_DIR)
	@make fclean -C $(LIBBUILTIN_DIR)
	$(RM) get_n_tok test_parser test_envmanager

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
