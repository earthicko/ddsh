/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_def.h"
#include "t_node.h"
#include "strutils.h"

static int	_expand_single_node(t_node *root)
{
	if (!(root->type == NODETYPE_CMD_WORD || root->type == NODETYPE_FILENAME))
		return (CODE_OK);
	return (do_shell_expansion(&(root->content)));
}

int	expand_node(t_node *root)
{
	t_list	*cursor;
	int		stat;

	if (!root)
		return (CODE_OK);
	if (!root->childs)
		return (_expand_single_node(root));
	stat = 0;
	cursor = root->childs;
	while (cursor)
	{
		stat = expand_node(cursor->content);
		if (stat)
			return (stat);
		cursor = cursor->next;
	}
	return (CODE_OK);
}
