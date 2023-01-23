/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_sequence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:53 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft_def.h"
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

static t_node	*_parse_pipe_sequence_loop(t_parser *p, t_node *root)
{
	t_node	*child;

	child = _parse_simple_command(p);
	if (!child)
		return (_parse_abort(p, root, NULL));
	if (node_addchild(root, child))
	{
		p->exit_stat = CODE_ERROR_MALLOC;
		return (_parse_abort(p, root, child));
	}
	if (_parser_is_last_token(p))
		return (root);
	if (p->tok_curr->type != TOKENTYPE_PIPE)
		return (_parse_abort(p, root, NULL));
	return ((t_node *)p);
}

t_node	*_parse_pipe_sequence(t_parser *p)
{
	t_node	*root;
	t_node	*status;

	root = node_create(NODETYPE_PIPE_SEQUENCE, NULL, 0);
	if (!root)
	{
		p->exit_stat = CODE_ERROR_MALLOC;
		return (NULL);
	}
	while (TRUE)
	{
		status = _parse_pipe_sequence_loop(p, root);
		if (status != (t_node *)p)
			return (status);
		p->tok_curr++;
		root->n_tokens++;
	}
}
