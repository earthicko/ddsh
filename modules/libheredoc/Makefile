NAME		= libheredoc.a

BASE_DIR	= ../..
INC_DIR		= \
			-I./includes \
			-I$(BASE_DIR)/modules/libft/includes \
			-I$(BASE_DIR)/modules/libenvman/includes \
			-I$(BASE_DIR)/modules/libparser/includes \
			-I$(BASE_DIR)/modules/liblexer/includes \
			-I$(BASE_DIR)/includes
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
