#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "strutils.h"
#include "envmanager.h"
#include "heredoc.h"
#include "lexer.h"
#include "parser.h"
#include "t_node.h"
#include "msgdef.h"
#include "testers.h"
#include "build_exec.h"
#include "executor.h"
#include "sighandler.h"

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_toks		toks;
	t_node		*parse_tree;
	t_unit_arr	units;
	int			stat;

	(void)argc;
	(void)argv;
	stat = envman_init(envp);
	if (stat)
		return (1);
	while (TRUE)
	{
		stat = signal_set_state_interactive();
		if (stat)
			return (1);
		heredoc_clear(-1);
		
		str = readline(MSG_SHELL_PROMPT);
		if (!str)
			exit(0);
		stat = signal_set_state_executing();
		if (stat)
			return (1);
		add_history(str);

		stat = lexer(str, &toks);
		free(str);
		if (toks.n_toks == 0)
		{
			token_destroy(&toks);
			system("leaks minishell");
			continue ;
		}
		if (stat)
		{
			exit_stat_manager(258);
			system("leaks minishell");
			continue ;
		}
		ft_printf("%s: lexer done\n", __func__, str);
		
		parse_tree = parse_tokens(toks.arr, toks.n_toks);
		token_destroy(&toks);
		if (!parse_tree)
		{
			ft_dprintf(2, "error while parsing\n");
			continue ;
		}
		ft_printf("%s: parsing done\n", __func__, str);
		node_print(parse_tree, 0);

		stat = expand_node(parse_tree);
		if (stat)
		{
			ft_print_error(MSG_ERROR_PREFIX, stat);
			system("leaks minishell");
			continue ;
		}

		stat = build_exec_unit(parse_tree, &units);
		node_destroy(parse_tree);
		if (stat)
		{
			ft_print_error(MSG_ERROR_PREFIX, stat);
			system("leaks minishell");
			continue ;
		}
		ft_printf("%s: exec build done\n\n\n", __func__, str);

		ft_printf(">===== 출력 <======\n\n");
		stat = executor(&units);
		exit_stat_manager(stat);
		units_destroy(&units);
		if (stat)
		{
			ft_print_error(MSG_ERROR_PREFIX, stat);
			system("leaks minishell");
			continue ;
		}
		ft_printf("%s: exec done\n\n\n", __func__, str);

		system("leaks minishell");
	}
	return (CODE_OK);
}
