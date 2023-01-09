#include "../includes/lexer.h"
#include "../libft/includes/libft.h"
#include "../srcs/lexer/lexer_utils.c"
#include "../srcs/lexer/init_toks.c"
#include "../srcs/lexer/is_char.c"
#include "../srcs/lexer/type_len.c"
#include "../srcs/lexer/lexer.c"

int	ft_strncmp(const char *s1, const char *s2, size_t n);

void	print_tok_arr(t_toks *toks)
{
	int	i;

	i = -1;
	while (++i < toks->n_toks)
	{
		printf("type: %d\n", toks->arr[i].type);
		printf("arr[%d]: %s\n", i, toks->arr[i].content);
	}
	printf("\n");
}

int	main(void)
{
	printf("tok 3: %d\n\n", get_n_toks("ab cd ef"));
	printf("tok 9: %d\n\n", get_n_toks("\"c\"a\'t\' >a -e >b 'file' >> c"));
	printf("tok 10: %d\n\n", get_n_toks("\"c\"a\'t\'bc >><a -e >b 'file'>>c"));
	printf("tok 10: %d\n\n", get_n_toks("\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c"));
	printf("tok 8: %d\n\n", get_n_toks("<<> <a>b >><"));
	printf("tok -1: %d\n\n", get_n_toks("\"c\"\"abc\'\t\'bc\' >><a -e >b 'file'>>c"));
	printf("toks :%d\n", get_n_toks("c\"a'b\" |>a ls -l"));
	printf("\n>================<\n\n\n");
	print_tok_arr(lexer("ab cd ef"));
	print_tok_arr(lexer("\"c\"a\'t\' >a -e >b 'file' >> c"));
	print_tok_arr(lexer("\"c\"a\'t\'bc >><a -e >b 'file'>>c"));
	print_tok_arr(lexer("\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c"));
	print_tok_arr(lexer("<<> <a>b >><"));
	print_tok_arr(lexer("\"c\"\"abc\'\t\'bc\' >><a -e >b 'file'>>c"));
	print_tok_arr(lexer(" c\"a'b\" |>a ls -l"));
	print_tok_arr(lexer(" c\"a'\tb\" |>a\t ls -l"));
}
