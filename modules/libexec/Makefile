NAME			= libexec.a
################################# COMMANDS #####################################
RM				= rm -f
CFLAGS			= -Wall -Werror -Wextra -MMD -MP -g
BASE_DIR		= ../..
INC_DIR			= \
				-I./includes \
				-I$(BASE_DIR)/modules/libft/includes \
				-I$(BASE_DIR)/modules/libparser/includes \
				-I$(BASE_DIR)/includes

include filelist.mk
################################# TARGETS ######################################
all:
	@make $(NAME)

$(NAME): $(OBJ_LIBEXEC)
	ar -rcs $(NAME) $(OBJ_LIBEXEC)

-include $(DEP_LIBLEXEC)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_LIBEXEC) $(DEP_LIBEXEC)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
