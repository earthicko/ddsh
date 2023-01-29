NAME		= liblexer.a

INC_DIR		:= $(INC_DIR) -I./includes
CFLAGS		= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
ARFLAGS		= rcs

include filelist.mk

all: $(NAME)

$(NAME): $(OBJ_LIBLEXER)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_LIBLEXER)

-include $(DEP_LIBLEXER)

clean:
	$(RM) $(OBJ_LIBLEXER) $(DEP_LIBLEXER)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
