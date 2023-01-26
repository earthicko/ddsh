/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_steps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:43:47 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:43:51 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
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
#include "executor.h"
#include "sighandler.h"
#include "builtin_commands.h"
#include "prompt_internal.h"

int	prompt_clear(void)
{
	if (signal_set_state_interactive())
		return (CODE_ERROR_GENERIC);
	heredoc_clear();
	return (CODE_OK);
}

int	prompt_getstr(char **buf)
{
	char	*str;
	char	*prefix;

	prefix = prompt_get_prompt_prefix();
	str = readline(prefix);
	free(prefix);
	if (!str)
		builtin_exit(NULL);
	if (signal_set_state_executing())
		return (CODE_ERROR_GENERIC);
	if (ft_strlen(str) > 0)
		add_history(str);
	*buf = str;
	return (CODE_OK);
}

int	prompt_gettokens(char *str, t_toks *toks)
{
	int	stat;

	stat = lexer(str, toks);
	if (toks->n_toks == 0)
	{
		token_destroy(toks);
		return (CODE_CONTINUE);
	}
	if (stat)
	{
		exit_stat_manager(258);
		return (CODE_CONTINUE);
	}
	return (CODE_OK);
}

int	prompt_getparsetree(t_toks *toks, t_node **buf)
{
	int	stat;

	*buf = parse_tokens(toks->arr, toks->n_toks);
	if (!*buf)
		return (CODE_CONTINUE);
	stat = expand_node(*buf);
	if (stat)
	{
		ft_print_error(MSG_ERROR_PREFIX, stat);
		return (CODE_CONTINUE);
	}
	return (CODE_OK);
}

int	prompt_execute(t_node *parse_tree)
{
	int	stat;

	stat = execute_tree(parse_tree);
	if (stat)
	{
		ft_print_error(MSG_ERROR_PREFIX, stat);
		return (CODE_CONTINUE);
	}
	return (CODE_OK);
}
