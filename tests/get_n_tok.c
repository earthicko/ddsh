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
		return ;
	while (++i < toks->n_toks)
	{
		printf("type: %d\n", toks->arr[i].type);
		printf("arr[%d]: %s\n", i, toks->arr[i].content);
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
	printf("\n>================<\n\n\n");
	/*
	if ((ret = lexer("ab cd ef", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("ret: %d\n", ret);
	*/
	if ((ret = lexer("\"c\"a\'t\' >a -e >b 'file' >> c", &toks)) == CODE_OK)
		print_tok_arr(&toks);
	else
		printf("ret: %d\n", ret);
	/*
	print_tok_arr(lexer("\"c\"a\'t\'bc >><a -e >b 'file'>>c"));
	print_tok_arr(lexer("\"c\"\"abc\'\"t\'bc\' >><a -e >b 'file'>>c"));
	print_tok_arr(lexer("<<> <a>b >><"));
	*/
	//
	//idx == 5에서, free걸어두면, 바로 아랫단, unclosed quote인데 toks를 해제하지 않아서 릭 잡힘
	/*
	print_tok_arr(lexer("\"c\"\"abc\'\t\'bc\' >><a -e >b 'file'>>c"));

	print_tok_arr(lexer(" c\"a'b\" |>a ls -l"));
	print_tok_arr(lexer(" c\"a'\tb\" |>a\t ls -l"));
	*/
	system("leaks get_n_tok");
}