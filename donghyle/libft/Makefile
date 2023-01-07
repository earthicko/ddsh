NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP
RM			= rm -f

SRCNAME		= \
			ft_asciitools \
			ft_asciitools2 \
			ft_memtools \
			ft_memtools2 \
			ft_strtools \
			ft_strtools2 \
			ft_strtools3 \
			ft_strtools4 \
			ft_strarrtools \
			ft_split \
			ft_split_by_chars \
			ft_atoi \
			ft_itoa \
			ft_put_fd \
			ft_lsttools \
			ft_lsttools2 \
			get_next_line \
			get_next_line_utils \
			ft_printf \
			ft_printf_t_conv \
			ft_printf_parse_format \
			ft_printf_parse_format_utils \
			ft_printf_create_str \
			ft_printf_create_str_utils \
			ft_printf_fwrite_chr \
			ft_printf_fwrite_num \
			ft_printf_fwrite_ptr \
			ft_printf_fwrite_utils \
			t_intarr \
			t_chararr

SRC			= $(addprefix src/, $(addsuffix .c, $(SRCNAME)))
OBJ			= $(addprefix src/, $(addsuffix .o, $(SRCNAME)))
DEP			= $(addprefix src/, $(addsuffix .d, $(SRCNAME)))

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean:
	make clean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY : all clean fclean re
