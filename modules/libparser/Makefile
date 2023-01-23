NAME		= libparser.a

BASE_DIR	= ../..
INC_DIR		= \
			-I./includes \
			-I$(BASE_DIR)/modules/libft/includes \
			-I$(BASE_DIR)/modules/libheredoc/includes \
			-I$(BASE_DIR)/modules/liblexer/includes \
			-I$(BASE_DIR)/modules/libenvman/includes \
			-I$(BASE_DIR)/includes
CFLAGS		= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
ARFLAGS		= rcs

include filelist.mk

all: $(NAME)

$(NAME): $(OBJ_LIBPARSER)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_LIBPARSER)

-include $(DEP_LIBPARSER)

clean:
	$(RM) $(OBJ_LIBPARSER) $(DEP_LIBPARSER)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
