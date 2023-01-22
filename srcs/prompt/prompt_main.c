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
#include "libft_def.h"
#include "envmanager.h"
#include "heredoc.h"
#include "lexer.h"
#include "t_node.h"
#include "prompt_internal.h"

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_toks		toks;
	t_node		*parse_tree;
	int			stat;

	(void)argc;
	(void)argv;
	envman_init(envp);
	heredoc_init();
	while (TRUE)
	{
		if (prompt_init() || prompt_getstr(&str))
			continue ;
		stat = prompt_gettokens(str, &toks);
		free(str);
		if (stat)
			continue ;
		stat = prompt_getparsetree(&toks, &parse_tree);
		token_destroy(&toks);
		if (stat)
			continue ;
		prompt_execute(parse_tree);
		node_destroy(parse_tree);
	}
	return (CODE_OK);
}
