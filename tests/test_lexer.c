#include "lexer.h"
#include "libft.h"
#include "libft_def.h"
#include <stdio.h>
#include <stdlib.h>

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

int	main(void)
{
	t_toks	toks;
	int	ret;
	// printf("tok 3: %d\n\n", get_n_toks("ab cd ef"));
	// printf("tok 9: %d\n\n", get_n_toks("\"c\"a\'t\' >a -e >b 'file' >> c"));
	// printf("tok 10: %d\n\n", get_n_toks("\"c\"a\'t\'bc >><a -e >b 'file'>>c"));
	// printf("tok 10: %d\n\n", get_n_toks("\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c"));
	// printf("tok 8: %d\n\n", get_n_toks("<<> <a>b >><"));
	// printf("tok -1: %d\n\n", get_n_toks("\"c\"\"abc\'\t\'bc\' >><a -e >b 'file'>>c"));
	// printf("toks :%d\n", get_n_toks("c\"a'b\" |>a ls -l"));
	printf("\n>================<\n\n");

	printf("input: %s\n\n", "ab cd ef");
	if ((ret = lexer("ab cd ef", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("code error: %d\n", ret);
	token_destroy(&toks);
	printf("\n>================<\n\n");

	printf("input: %s\n\n", "\"c\"a\'t\' >a -e >b 'file' >> c");
	if ((ret = lexer("\"c\"a\'t\' >a -e >b 'file' >> c", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("code error: %d\n", ret);
	token_destroy(&toks);
	printf("\n>================<\n\n");
	
	printf("input: %s\n\n", "\"c\"a\'t\'bc >><a -e >b 'file'>>c");
	if ((ret = lexer("\"c\"a\'t\'bc >><a -e >b 'file'>>c", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("code error: %d\n", ret);
	token_destroy(&toks);
	printf("\n>================<\n\n");

	printf("input: %s\n\n", "\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c");
	if ((ret = lexer("\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("code error: %d\n", ret);
	token_destroy(&toks);
	printf("\n>================<\n\n");

	printf("input: %s\n\n", "<<> <a>b >><");
	if ((ret = lexer("<<> <a>b >><", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("code error: %d\n", ret);
	token_destroy(&toks);
	printf("\n>================<\n\n");

	printf("input: %s\n\n", "<<> <a>b >><");
	if ((ret = lexer("<<> <a>b >><", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("code error: %d\n", ret);
	token_destroy(&toks);
	printf("\n>================<\n\n");

	//idx == 5에서, free걸어두면, 바로 아랫단, unclosed quote인데 toks를 해제하지 않아서 릭 잡힘
	printf("input: %s\n\n", "\"c\"\"abc\'\t\'bc\' >><a -e >b 'file'>>c");
	if ((ret = lexer("\"c\"\"abc\'\t\'bc\' >><a -e >b 'file'>>c", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("code error: %d\n", ret);
	token_destroy(&toks);
	printf("\n>================<\n\n");

	printf("input: %s\n\n", " c\"a'b\" |>a ls -l");
	if ((ret = lexer(" c\"a'b\" |>a ls -l", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("code error: %d\n", ret);
	token_destroy(&toks);
	printf("\n>================<\n\n");

	printf("input: %s\n\n", " c\"a'\tb\" |>a\t ls -l");
	if ((ret = lexer(" c\"a'\tb\" |>a\t ls -l", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("code error: %d\n", ret);
	token_destroy(&toks);
	system("leaks test_lexer");
}
