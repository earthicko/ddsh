/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:43:47 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:43:51 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"
#include "builtin_commands.h"
#include "heredoc.h"
#include "lexer.h"
#include "t_node.h"
#include "msgdef.h"
#include "prompt_internal.h"

void	execute_line(char *line)
{
	int		stat;
	t_toks	toks;
	t_node	*parse_tree;
	char	*clean_line;

	clean_line = trunc_comments(line);
	if (!clean_line)
	{
		ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
		return ;
	}
	stat = prompt_gettokens(clean_line, &toks);
	free(clean_line);
	if (stat)
		return ;
	stat = prompt_getparsetree(&toks, &parse_tree);
	token_destroy(&toks);
	if (stat)
		return ;
	prompt_execute(parse_tree);
	node_destroy(parse_tree);
	return ;
}

static void	_prompt_init(char **envp)
{
	envman_init(envp);
	heredoc_init();
	prompt_clear();
	execute_line("source $HOME/.dshrc");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	_prompt_init(envp);
	if (argc > 1)
	{
		builtin_dot(argv);
		return (exit_stat_manager(-1));
	}
	prompt_print_banner();
	while (TRUE)
	{
		if (prompt_clear() || prompt_getstr(&line))
			continue ;
		execute_line(line);
		free(line);
	}
	return (exit_stat_manager(-1));
}
