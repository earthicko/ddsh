NAME		= libexpansion.a

BASE_DIR	= ../..
INC_DIR		= \
			-I./includes \
			-I$(BASE_DIR)/includes \
			-I$(BASE_DIR)/modules/libft/includes \
			-I$(BASE_DIR)/modules/libenvman/includes \
			-I$(BASE_DIR)/modules/liblexer/includes \
			-I$(BASE_DIR)/modules/libparser/includes
CFLAGS		= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
ARFLAGS		= rcs

include filelist.mk

all: $(NAME)

$(NAME): $(OBJ_LIBEXPANSION)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_LIBEXPANSION)

-include $(DEP_LIBLEXPANSION)

clean:
	$(RM) $(OBJ_LIBEXPANSION) $(DEP_LIBEXPANSION)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
