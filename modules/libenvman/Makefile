NAME		= libenvman.a

INC_DIR		:= $(INC_DIR) -I./includes
CFLAGS		= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
ARFLAGS		= rcs

include filelist.mk

all: $(NAME)

$(NAME): $(OBJ_LIBENVMAN)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_LIBENVMAN)

-include $(DEP_LIBENVMAN)

clean:
	$(RM) $(OBJ_LIBENVMAN) $(DEP_LIBENVMAN)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
