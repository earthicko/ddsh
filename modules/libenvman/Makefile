NAME			= libenvman.a
################################# COMMANDS #####################################
RM				= rm -f
CFLAGS			= -Wall -Werror -Wextra -MMD -MP -g
BASE_DIR		= ../..
INC_DIR			= \
				-I./includes \
				-I$(BASE_DIR)/modules/libft/includes \
				-I$(BASE_DIR)/includes
################################ FILENAMES #####################################
FILENAME		= \
				t_enventry \
				envmanager_getenvp \
				envmanager_init \
				envmanager_setval \
				envmanager_utils \
				envmanager_clear \
				envmanager_getval \
				envmanager_unsetval \
				envmanager

SRC				= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))
################################# TARGETS ######################################
all:
	@make $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
