NAME			= 
################################# LIBRARIES ####################################
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LINK_LIBFT		= -L$(LIBFT_DIR)
INC_DIR_LIBFT	= -I$(LIBFT_DIR)/includes

LIB_ALL			= $(LIBFT)
LINK_LIBS		= $(LINK_LIBFT)

INC_DIR_M		= -I. $(INC_DIR_LIBFT) -Iincludes_mandatory
INC_DIR_B		= -I. $(INC_DIR_LIBFT) -Iincludes_bonus
################################# COMMANDS #####################################
RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP
################################ FILENAMES #####################################
NAME_M			= \
NAME_B			= \

SRC_M			= $(addprefix src_mandatory/, $(addsuffix .c, $(NAME_M)))
OBJ_M			= $(addprefix src_mandatory/, $(addsuffix .o, $(NAME_M)))
DEP_M			= $(addprefix src_mandatory/, $(addsuffix .d, $(NAME_M)))
STAT_M			= mandatory.log

SRC_B			= $(addprefix src_bonus/, $(addsuffix .c, $(NAME_B)))
OBJ_B			= $(addprefix src_bonus/, $(addsuffix .o, $(NAME_B)))
DEP_B			= $(addprefix src_bonus/, $(addsuffix .d, $(NAME_B)))
STAT_B			= bonus.log
################################# SRC SET ######################################
ifdef TARGET
ifeq ($(TARGET), MANDATORY)
SRC				= $(SRC_M)
OBJ				= $(OBJ_M)
DEP				= $(DEP_M)
INC_DIR			= $(INC_DIR_M)
STAT			= $(STAT_M)
endif
ifeq ($(TARGET), BONUS)
SRC				= $(SRC_B)
OBJ				= $(OBJ_B)
DEP				= $(DEP_B)
INC_DIR			= $(INC_DIR_B)
STAT			= $(STAT_B)
endif
else
SRC				= $(SRC_M)
OBJ				= $(OBJ_M)
DEP				= $(DEP_M)
INC_DIR			= $(INC_DIR_M)
STAT			= $(STAT_M)
endif
################################# TARGETS ######################################
all:
	@make TARGET=MANDATORY $(NAME)

bonus:
	@make TARGET=BONUS $(NAME)

$(NAME): $(LIB_ALL) $(OBJ) $(STAT)
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_LIBS) $(LIBFT) $(LIBMLX) $(OBJ) -o $@

$(LIBFT):
	@make -j4 -C $(LIBFT_DIR)/

$(STAT_M): $(OBJ_M)
	rm -f $(STAT_B)
	touch $(STAT_M)

$(STAT_B): $(OBJ_B)
	rm -f $(STAT_M)
	touch $(STAT_B)

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_M) $(OBJ_B) $(DEP_M) $(DEP_B) $(STAT_M) $(STAT_B)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS)
	@make fclean -C $(LIBFT_DIR)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
