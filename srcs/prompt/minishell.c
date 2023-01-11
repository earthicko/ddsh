#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_node.h"
#include "strings.h"
#include "testers.h"

int	main(void)
{
	char	*str;
	t_toks	toks;
	t_node	*exec_tree;
	int		stat;

	while (TRUE)
	{
		str = readline(MSG_SHELL_PROMPT);
		if (!str)
			continue ;
		if (ft_strlen(str) == 0)
			continue ;
		add_history(str);
		stat = lexer(str, &toks);
		free(str);
		if (stat)
			continue ;
		exec_tree = parse_tokens(toks.arr, toks.n_toks);
		// toks_destroy(&toks);
		if (exec_tree)
			node_print(exec_tree, 0);
		node_destroy(exec_tree);
		system("leaks minishell");
	}
	return (CODE_OK);
}
