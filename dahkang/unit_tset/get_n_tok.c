#include "../includes/lexer.h"
#include "../srcs/is_char.c"
#include "../srcs/skip_str.c"
#include "../srcs/lexer.c"

int	main(void)
{
	printf("tok 3: %d\n", get_n_toks("ab cd ef"));
	printf("tok 9: %d\n", get_n_toks("\"c\"a\'t\' >a -e >b 'file' >> c"));
	printf("tok 10: %d\n", get_n_toks("\"c\"a\'t\'bc >><a -e >b 'file'>>c"));
	printf("tok 10: %d\n", get_n_toks("\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c"));
	printf("tok 8: %d\n", get_n_toks("<<> <a>b >><"));
	return (0);
}
