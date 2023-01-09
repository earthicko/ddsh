#include "../includes/lexer.h"
#include "../libft/includes/libft.h"
#include "../srcs/lexer_utils.c"
#include "../srcs/init_toks.c"
#include "../srcs/is_char.c"
#include "../srcs/skip_str.c"
#include "../srcs/lexer.c"

int	ft_strncmp(const char *s1, const char *s2, size_t n);

void	print_tok_arr(t_toks *toks)
{
	int	i;

	i = -1;
	while (++i < toks->n_toks)
		printf("arr[%d]: %s\n", i, toks->arr[i].content);
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
	printf("\n>================<\n\n\n");
	print_tok_arr(lexer("ab cd ef"));
	print_tok_arr(lexer("\"c\"a\'t\' >a -e >b 'file' >> c"));
	print_tok_arr(lexer("\"c\"a\'t\'bc >><a -e >b 'file'>>c"));
	print_tok_arr(lexer("\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c"));
	print_tok_arr(lexer("<<> <a>b >><"));
	print_tok_arr(lexer("\"c\"\"abc\'\t\'bc\' >><a -e >b 'file'>>c"));
}
