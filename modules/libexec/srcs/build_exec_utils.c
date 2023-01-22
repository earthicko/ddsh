/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:45 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec_internal.h"

int	get_n_unit(t_node *root)
{
	int		n_unit;
	t_list	*curr;

	n_unit = 0;
	curr = root->childs;
	while (curr)
	{
		curr = curr->next;
		n_unit++;
	}
	return (n_unit);
}

int	get_n_redir(t_node *node)
{
	int		n_redir;
	t_list	*cursor;
	t_node	*curr;

	n_redir = 0;
	cursor = node->childs;
	while (cursor)
	{
		curr = cursor->content;
		curr = curr->childs->content;
		if (curr->type == NODETYPE_IO_REDIRECT)
			n_redir++;
		cursor = cursor->next;
	}
	return (n_redir);
}

t_node	*get_child_node(t_node *node, int depth)
{
	t_node	*ret;
	int		i;

	ret = node;
	i = -1;
	while (++i < depth)
	{
		if (ret->childs)
			ret = ret->childs->content;
		else
		{
			ft_dprintf(2, "Exceed depth range: Current node has no child\n");
			ft_dprintf(2, "Current depth is %d\n", i);
		}
	}
	return (ret);
}
