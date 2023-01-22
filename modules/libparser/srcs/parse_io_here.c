/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:53 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "heredoc.h"
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*_parse_io_here(t_parser *p)
{
	int		stat;
	t_node	*root;

	root = node_create(NODETYPE_IO_HERE, NULL, 0);
	if (!root)
	{
		p->exit_stat = CODE_ERROR_MALLOC;
		return (_parse_abort(p, NULL, NULL));
	}
	if (_parse_terminal_and_addchild(p, NODETYPE_IO_OP_HERE, root))
		return (NULL);
	if (_parse_terminal_and_addchild(p, NODETYPE_HERE_END, root))
		return (NULL);
	stat = heredoc_read(((t_node *)root->childs->next->content)->content);
	if (stat)
	{
		p->exit_stat = stat;
		return (node_destroy(root));
	}
	return (root);
}
