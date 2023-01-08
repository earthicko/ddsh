NAME			= libparser.a
################################# COMMANDS #####################################
RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP -g
BASE_DIR		= ../../
INC_DIR			= \
				-I./includes \
				-I$(BASE_DIR)modules/libft/includes \
				-I$(BASE_DIR)includes
################################ FILENAMES #####################################
FILENAME		= \
				t_node \
				parser_util \
				parser_util1 \
				parser_util2 \
				parser_util3 \
				parser

SRC				= $(addsuffix .c, $(FILENAME))
OBJ				= $(addsuffix .o, $(FILENAME))
DEP				= $(addsuffix .d, $(FILENAME))
################################# TARGETS ######################################
all:
	@make $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
