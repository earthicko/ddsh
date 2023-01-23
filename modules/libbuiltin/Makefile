NAME		= libbuiltin.a

BASE_DIR	= ../..
INC_DIR		= \
			-I./includes \
			-I$(BASE_DIR)/modules/libft/includes \
			-I$(BASE_DIR)/modules/libparser/includes \
			-I$(BASE_DIR)/modules/libenvman/includes \
			-I$(BASE_DIR)/includes
CFLAGS		= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
ARFLAGS		= rcs

include filelist.mk

all: $(NAME)

$(NAME): $(OBJ_LIBBUILTIN)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_LIBBUILTIN)

-include $(DEP_LIBBUILTIN)

clean:
	$(RM) $(OBJ_LIBBUILTIN) $(DEP_LIBBUILTIN)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
