NAME				= minishell
################################# LIBRARIES ####################################
LIB_DIR				= modules

LIBFT_DIR			= $(LIB_DIR)/libft
LIBFT				= $(LIBFT_DIR)/libft.a
LINK_LIBFT			= -L$(LIBFT_DIR)
INC_DIR_LIBFT		= -I$(LIBFT_DIR)/includes

LIBPARSER_DIR		= $(LIB_DIR)/libparser
LIBPARSER			= $(LIBPARSER_DIR)/libparser.a
LINK_LIBPARSER		= -L$(LIBPARSER_DIR)
INC_DIR_LIBPARSER	= -I$(LIBPARSER_DIR)/includes

LIBENVMAN_DIR		= $(LIB_DIR)/libenvman
LIBENVMAN			= $(LIBENVMAN_DIR)/libenvman.a
LINK_LIBENVMAN		= -L$(LIBENVMAN_DIR)
INC_DIR_LIBENVMAN	= -I$(LIBENVMAN_DIR)/includes

LIB_ALL				= $(LIBFT) $(LIBPARSER) $(LIBENVMAN)
LINK_LIBS			= $(LINK_LIBFT) $(LINK_LIBPARSER) $(LINK_LIBENVMAN)

INC_DIR				= -I. -Iincludes \
					$(INC_DIR_LIBFT) \
					$(INC_DIR_LIBPARSER) \
					$(INC_DIR_LIBENVMAN)
################################# COMMANDS #####################################
RM					= rm -f
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -MMD -MP -g
################################ FILENAMES #####################################
FILENAME			= \
					main

SRC					= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ					= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP					= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))

TEST_FILENAME		= \
					testers/print_nodes \
					testers/print_tokens
TEST_SRC			= $(addsuffix .c, $(TEST_FILENAME))
TEST_OBJ			= $(addsuffix .o, $(TEST_FILENAME))
TEST_DEP			= $(addsuffix .d, $(TEST_FILENAME))
################################# TARGETS ######################################
all:
	@make $(NAME)

$(NAME): $(LIB_ALL) $(OBJ)
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_LIBS) $(LIB_ALL) $(OBJ) -o $@

test_parser: $(LIB_ALL) $(TEST_OBJ) testers/test_parser.o
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_LIBS) $(LIB_ALL) $(TEST_OBJ) testers/test_parser.o -o $@

test_envmanager: $(LIB_ALL) $(TEST_OBJ) testers/test_envmanager.o
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_LIBS) $(LIB_ALL) $(TEST_OBJ) testers/test_envmanager.o -o $@

$(LIBFT):
	@make -j4 -C $(LIBFT_DIR)/

$(LIBPARSER):
	@make -j4 -C $(LIBPARSER_DIR)/

$(LIBENVMAN):
	@make -j4 -C $(LIBENVMAN_DIR)/

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP) $(TEST_OBJ) $(TEST_DEP)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBPARSER_DIR)
	@make clean -C $(LIBENVMAN_DIR)
	$(RM) testers/test_parser.o testers/test_parser.d testers/test_envmanager.o testers/test_envmanager.d

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBPARSER_DIR)
	@make fclean -C $(LIBENVMAN_DIR)
	$(RM) test_parser test_envmanager

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
