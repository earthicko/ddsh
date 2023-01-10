NAME			= libparser.a
################################# COMMANDS #####################################
RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP -g
BASE_DIR		= ../..
INC_DIR			= \
				-I./includes \
				-I$(BASE_DIR)/modules/libft/includes \
				-I$(BASE_DIR)/modules/liblexer/includes \
				-I$(BASE_DIR)/includes

include filelist.mk
################################# TARGETS ######################################
all:
	@make $(NAME)

$(NAME): $(OBJ_LIBPARSER)
	ar -rcs $(NAME) $(OBJ_LIBPARSER)

-include $(DEP_LIBPARSER)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_LIBPARSER) $(DEP_LIBPARSER)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
