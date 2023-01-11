NAME			= libheredoc.a
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

$(NAME): $(OBJ_LIBHEREDOC)
	ar -rcs $(NAME) $(OBJ_LIBHEREDOC)

-include $(DEP_LIBHEREDOC)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_LIBHEREDOC) $(DEP_LIBHEREDOC)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
