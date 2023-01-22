/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:53 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*_parse_io_file(t_parser *p)
{
	t_node	*root;

	root = node_create(NODETYPE_IO_FILE, NULL, 0);
	if (!root)
	{
		p->exit_stat = CODE_ERROR_MALLOC;
		return (_parse_abort(p, NULL, NULL));
	}
	if (_parse_terminal_and_addchild(p, NODETYPE_IO_OP_FILE, root))
		return (NULL);
	if (_parse_terminal_and_addchild(p, NODETYPE_FILENAME, root))
		return (NULL);
	return (root);
}
