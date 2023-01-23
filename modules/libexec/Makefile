NAME		= libexec.a

BASE_DIR	= ../..
INC_DIR		= \
			-I./includes \
			-I$(BASE_DIR)/modules/libft/includes \
			-I$(BASE_DIR)/modules/libenvman/includes \
			-I$(BASE_DIR)/modules/libparser/includes \
			-I$(BASE_DIR)/modules/libheredoc/includes \
			-I$(BASE_DIR)/modules/libbuiltin/includes \
			-I$(BASE_DIR)/includes
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
