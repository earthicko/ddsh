/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_terminal.c                                   :+:      :+:    :+:   */
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

static int	_is_correct_tokentype(int nodetype, int tokentype)
{
	int		token_map[N_TOKENTYPE];
	void	(*map_setter[N_NODETYPE])(int *);

	map_setter[NODETYPE_CMD_WORD] = _map_setter_cmd_word;
	map_setter[NODETYPE_IO_OP_FILE] = _map_setter_io_op_file;
	map_setter[NODETYPE_FILENAME] = _map_setter_filename;
	map_setter[NODETYPE_IO_OP_HERE] = _map_setter_io_op_here;
	map_setter[NODETYPE_HERE_END] = _map_setter_here_end;
	(map_setter[nodetype])(token_map);
	return (token_map[tokentype]);
}

t_node	*_parse_terminal(t_parser *p, int nodetype)
{
	t_node	*root;

	if (_parser_is_last_token(p))
	{
		p->last_error_loc = p->tok_curr;
		return (NULL);
	}
	if (!_is_correct_tokentype(nodetype, p->tok_curr->type))
	{
		p->last_error_loc = p->tok_curr;
		return (NULL);
	}
	root = node_create(nodetype, p->tok_curr->content, 1);
	if (!root)
	{
		p->exit_stat = CODE_ERROR_MALLOC;
		return (NULL);
	}
	p->tok_curr++;
	return (root);
}
