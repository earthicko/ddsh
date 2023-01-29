NAME		= libexec.a

INC_DIR		:= $(INC_DIR) -I./includes
CFLAGS		= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
ARFLAGS		= rcs

include filelist.mk

all: $(NAME)

$(NAME): $(OBJ_LIBEXEC)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_LIBEXEC)

-include $(DEP_LIBLEXEC)

clean:
	$(RM) $(OBJ_LIBEXEC) $(DEP_LIBEXEC)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
