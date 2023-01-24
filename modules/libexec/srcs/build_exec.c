/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:45 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "executor_internal.h"

static int	_init_unit(t_execunit *unit, t_node *simple_cmd)
{
	const int	n_redir = _get_n_redir(simple_cmd);
	const int	n_word = node_getntokens(simple_cmd) - 2 * n_redir;

	unit->argv = malloc(sizeof(char *) * (n_word + 1));
	unit->redir_arr = malloc(sizeof(t_redir) * (n_redir + 1));
	unit->n_word = n_word;
	unit->n_redir = n_redir;
	ft_bzero(unit->argv, sizeof(char *) * (n_word + 1));
	ft_bzero(unit->redir_arr, sizeof(t_redir) * (n_redir + 1));
	if (!unit->argv || !unit->redir_arr)
		return (_free_unit_member(unit));
	return (CODE_OK);
}

static int	_set_argv(t_node *node, t_execunit *unit, int idx)
{
	unit->argv[idx] = ft_strdup(node->content);
	if (!unit->argv[idx])
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

static int	_set_redir_arr(t_node *node, t_execunit *unit, int idx)
{
	t_node	*terminal_node;
	t_list	*curr;

	node = _get_child_node(node, 1);
	curr = node->childs;
	terminal_node = curr->content;
	if (ft_strncmp(terminal_node->content, "<<", 2) == 0)
		unit->redir_arr[idx].type = REDIR_IN_HERE;
	else if (ft_strncmp(terminal_node->content, ">>", 2) == 0)
		unit->redir_arr[idx].type = REDIR_OUT_APPEND;
	else if (ft_strncmp(terminal_node->content, "<", 1) == 0)
		unit->redir_arr[idx].type = REDIR_IN;
	else if (ft_strncmp(terminal_node->content, ">", 1) == 0)
		unit->redir_arr[idx].type = REDIR_OUT;
	else
		unit->redir_arr[idx].type = CODE_ERROR_DATA;
	terminal_node = curr->next->content;
	unit->redir_arr[idx].content = ft_strdup(terminal_node->content);
	if (!unit->redir_arr[idx].content)
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

static int	_build_unit(t_execunit *unit, t_node *simple_cmd)
{
	int		i;
	int		j;
	t_node	*node;
	t_list	*curr;

	if (_init_unit(unit, simple_cmd) == CODE_ERROR_MALLOC)
		return (CODE_ERROR_MALLOC);
	i = 0;
	j = 0;
	curr = simple_cmd->childs;
	while (curr)
	{
		node = _get_child_node(curr->content, 1);
		if (node->type == NODETYPE_CMD_WORD)
		{
			if (_set_argv(node, unit, i++) == CODE_ERROR_MALLOC)
				return (_free_single_unit(unit));
		}
		else
			if (_set_redir_arr(node, unit, j++) == CODE_ERROR_MALLOC)
				return (_free_single_unit(unit));
		curr = curr->next;
	}
	return (CODE_OK);
}

int	_build_exec_unit(t_node *root, t_execunit **units, int *n_units)
{
	const int	n_unit = _get_n_unit(root);
	t_list		*curr;
	int			idx;

	*units = malloc(sizeof(t_execunit) * n_unit);
	if (!*units)
		return (CODE_ERROR_MALLOC);
	ft_bzero(*units, n_unit * sizeof(t_execunit));
	curr = root->childs;
	idx = 0;
	while (idx < n_unit)
	{
		if (_build_unit(units[idx], curr->content) == CODE_ERROR_MALLOC)
			return (_free_all_unit(*units, n_unit));
		curr = curr->next;
		idx++;
	}
	*n_units = n_unit;
	return (CODE_OK);
}
