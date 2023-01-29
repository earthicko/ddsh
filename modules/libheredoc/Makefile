NAME		= libheredoc.a

INC_DIR		:= $(INC_DIR) -I./includes
CFLAGS		= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
ARFLAGS		= rcs

include filelist.mk

all: $(NAME)

$(NAME): $(OBJ_LIBHEREDOC)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_LIBHEREDOC)

-include $(DEP_LIBHEREDOC)

clean:
	$(RM) $(OBJ_LIBHEREDOC) $(DEP_LIBHEREDOC)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
