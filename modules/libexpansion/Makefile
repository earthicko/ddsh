NAME		= libexpansion.a

INC_DIR		:= $(INC_DIR) -I./includes
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
