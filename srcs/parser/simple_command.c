/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
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

t_node	*_parse_simple_command(t_parser *p)
{
	t_node	*root;
	t_node	*child;

	root = node_create(NODETYPE_SIMPLE_COMMAND, NULL, 0);
	if (!root)
	{
		p->exit_stat = CODE_ERROR_MALLOC;
		return (NULL);
	}
	while (TRUE)
	{
		child = _parse_cmd_element(p);
		if (!child)
		{
			if (node_getntokens(root))
				return (root);
			return (_parse_abort(p, root, NULL));
		}
		if (node_addchild(root, child))
		{
			p->exit_stat = CODE_ERROR_MALLOC;
			return (_parse_abort(p, root, child));
		}
	}
}
