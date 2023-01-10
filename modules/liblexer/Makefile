NAME			= liblexer.a
################################# COMMANDS #####################################
RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP -g
BASE_DIR		= ../..
INC_DIR			= \
				-I./includes \
				-I$(BASE_DIR)/modules/libft/includes \
				-I$(BASE_DIR)/includes

include filelist.mk
################################# TARGETS ######################################
all:
	@make $(NAME)

$(NAME): $(OBJ_LIBLEXER)
	ar -rcs $(NAME) $(OBJ_LIBLEXER)

-include $(DEP_LIBLEXER)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_LIBLEXER) $(DEP_LIBLEXER)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
