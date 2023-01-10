#include <readline/readline.h>
#include "libft_def.h"
#include "lexer.h"
#include "parser.h"
#include "t_node.h"

void	print_tok_arr(t_toks *toks)
{
	int	i;

	i = -1;
	if (!toks)
	{
		printf("toks is null\n\n");
		return ;
	}
	while (++i < toks->n_toks)
	{
		printf("type: %d\n", toks->arr[i].type);
		printf("arr[%d]: %s\n", i, toks->arr[i].content);
	}
	printf("\n");
}

int	main(void)
{
	char	*str;
	t_toks	toks;
	t_node	*exec_tree;

	while (1)
	{
		str = readline("minishell: ");
		if (lexer(str, &toks) == CODE_OK)
			exec_tree = parse_tokens(&toks->arr, &toks->n_toks);
		if (exec_tree)
			excute_cmd(exec_tree);
	}
}
