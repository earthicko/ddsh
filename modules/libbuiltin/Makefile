NAME		= libbuiltin.a

INC_DIR		:= $(INC_DIR) -I./includes
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
