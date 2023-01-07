CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

INCLUDES_DIR	= includes
LIBFT_DIR		= srcs/libft
GNL_DIR			= srcs/get_next_line
FT_PRINTF_DIR	= srcs/ft_printf

LIBFT = ft_isalpha.c 	\
	   ft_isdigit.c 	\
	   ft_isalnum.c 	\
	   ft_isascii.c 	\
	   ft_isprint.c 	\
	   					\
	   ft_strlen.c		\
	   ft_memset.c		\
	   ft_bzero.c		\
	   ft_memcpy.c		\
	   ft_memmove.c		\
	   ft_strlcpy.c		\
	   ft_strlcat.c		\
	   ft_strncmp.c		\
	   					\
	   ft_toupper.c 	\
	   ft_tolower.c 	\
	   					\
	   ft_strchr.c		\
	   ft_strrchr.c		\
	   ft_memchr.c		\
	   ft_memcmp.c		\
	   ft_strnstr.c		\
						\
	   ft_atoi.c		\
	   ft_strdup.c		\
	   ft_calloc.c		\
	   \
	   ft_substr.c		\
	   ft_strjoin.c		\
	   ft_strtrim.c		\
	   ft_split.c		\
	   ft_itoa.c		\
	   ft_strmapi.c		\
	   ft_striteri.c	\
	   ft_putchar_fd.c	\
	   ft_putstr_fd.c	\
	   ft_putendl_fd.c	\
	   ft_putnbr_fd.c	\
	   \
	   ft_lstnew.c	\
	   ft_lstadd_front.c \
	   ft_lstsize.c \
	   ft_lstlast.c \
	   ft_lstadd_back.c \
	   ft_lstdelone.c \
	   ft_lstclear.c \
	   ft_lstiter.c \
	   ft_lstmap.c \
	   \
	   ft_err_exit.c

GNL = get_next_line_bonus.c \
	  get_next_line_utils_bonus.c

FT_PRINTF = ft_printf.c \
			ft_printf_numeric.c \
			ft_printf_str.c \
			ft_printf_utils.c \

OBJS = $(addprefix $(LIBFT_DIR)/, $(LIBFT:.c=.o))\
		$(addprefix $(GNL_DIR)/, $(GNL:.c=.o)) \
		$(addprefix $(FT_PRINTF_DIR)/, $(FT_PRINTF:.c=.o))\

$(NAME): $(OBJS)
	ar rcs $@ $?
	
all: $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES_DIR)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: clean fclean re all
