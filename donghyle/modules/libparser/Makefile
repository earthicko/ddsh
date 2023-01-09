NAME			= libparser.a
################################# COMMANDS #####################################
RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP -g
BASE_DIR		= ../..
INC_DIR			= \
				-I./includes \
				-I$(BASE_DIR)/modules/libft/includes \
				-I$(BASE_DIR)/includes
################################ FILENAMES #####################################
FILENAME		= \
				t_node \
				parse_util \
				parse_io_file \
				parse_io_redirect \
				parse_simple_command \
				parse_cmd_element \
				parse_io_here \
				parse_pipe_sequence \
				parse_terminal \
				parser

SRC				= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))
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
