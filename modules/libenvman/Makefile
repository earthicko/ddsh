NAME			= libenvman.a
################################# COMMANDS #####################################
RM				= rm -f
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

$(NAME): $(OBJ_LIBENVMAN)
	ar -rcs $(NAME) $(OBJ_LIBENVMAN)

-include $(DEP_LIBENVMAN)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_LIBENVMAN) $(DEP_LIBENVMAN)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
