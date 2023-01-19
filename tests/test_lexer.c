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
	printf("%s, n_toks: %d\n", __func__, toks->n_toks);
	printf("%s, arr[0].content: %s\n", __func__, toks->arr[0].content);
	printf("%s, arr[0].type: %d\n", __func__, toks->arr[0].type);
	printf("\n");
}

void	test_lexer(char *str)
{
	t_toks	toks;
	int		ret;

	(void)str;
	printf("\n>================<\n\n");
	printf("input: %s\n\n", str);
	if ((ret = lexer(str, &toks)) != CODE_OK)
		printf("code error: %d\n", ret);
	else
		print_tok_arr(&toks);
	printf("\n");
	token_destroy(&toks);
}

// TEST: 인자로 "" 들어오면 널토큰 한개 파싱 (n_toks = 0)
// 인자로 널 들어오면 렉서에서 오류코드 반환
//
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
	/******빈문자열, 널************/
	commands[11] = "";
	commands[12] = 0;
}

int	main(void)
{
	int		i;
	char	*commands[13];

	set_commands(commands);
	i = 0;
	(void)i;
	/*
	while (i < 13)
	{
		test_lexer(commands[i]);
		i++;
	}
	*/
	test_lexer(commands[11]);
	system("leaks test_lexer");
	return (0);
}
