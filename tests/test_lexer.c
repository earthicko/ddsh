#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "libft.h"
#include "libft_def.h"

void	print_tok_arr(t_toks *toks)
{
	int	i;

	i = -1;
	if (!toks->arr)
	{
		printf("toks->arr is null\n\n");
		return ;
	}
	while (++i < toks->n_toks)
	{
		printf("type: %d\n", toks->arr[i].type);
		printf("arr[%d]: %s\n\n", i, toks->arr[i].content);
	}
	printf("\n");
}

void	test_lexer(char *str)
{
	t_toks	toks;
	int		ret;

	printf("\n>================<\n\n");
	printf("input: %s\n\n", "ab cd ef");
	if (lexer("ab cd ef", &toks))
		printf("code error: %d\n", ret);
	else
		print_tok_arr(&toks);
	token_destroy(&toks);
}

void	set_commands(char **commands)
{
	commands[0] = "ab cd ef";
	commands[1] = "\"c\"a\'t\' >a -e >b 'file' >> c";
	commands[2] = "\"c\"a\'t\'bc >><a -e >b 'file'>>c";
	commands[3] = "\"c\"a\'t\'bc >><a -e >b 'file'>>c";
	commands[4] = "\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c";
	commands[5] = "\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c";
	commands[6] = "<<> <a>b >><";
	commands[7] = "\"c\"\"abc\'\t\'bc\' >><a -e >b 'file'>>c";
	commands[8] = " c\"a'b\" |>a ls -l";
	commands[9] = " c\"a'\tb\" |>a\t ls -l";
	commands[10] = "\"\"";
}

int	main(void)
{
	int		i;
	char	*commands[11];

	set_commands(commands);
	i = 0;
	while (i < 11)
	{
		test_lexer(commands[i]);
		i++;
	}
	system("leaks test_lexer");
	return (0);
}
