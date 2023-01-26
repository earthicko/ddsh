/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_simplecom.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:09:48 by earth             #+#    #+#             */
/*   Updated: 2023/01/27 02:09:49 by earth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "t_node.h"
#include "t_execunit.h"

static int	_exec_simplecom_create_loop(
		t_node *root, t_exec_simplecom *exec, int i)
{
	void	*content;

	content = exec_arg_create(_get_nth_child(_get_nth_child(root, i), 0));
	if (content)
	{
		if (exec_lstadd(&(exec->args), content))
			return (CODE_ERROR_MALLOC);
		return (CODE_OK);
	}
	content = exec_redir_create(_get_nth_child(_get_nth_child(root, i), 0));
	if (content)
	{
		if (exec_lstadd(&(exec->redirs), content))
			return (CODE_ERROR_MALLOC);
		return (CODE_OK);
	}
	return (CODE_ERROR_DATA);
}

t_exec_simplecom	*exec_simplecom_create(t_node *root)
{
	t_exec_simplecom	*exec;
	int					len;
	int					i;

	if (root->type != NODETYPE_SIMPLE_COMMAND)
		return (NULL);
	exec = malloc(sizeof(t_exec_simplecom));
	if (!exec)
		return (NULL);
	ft_bzero(exec, sizeof(t_exec_simplecom));
	len = ft_lstsize(root->childs);
	i = 0;
	while (i < len)
	{
		if (_exec_simplecom_create_loop(root, exec, i))
			return (exec_simplecom_destroy(exec));
		i++;
	}
	return (exec);
}

static void	_del_redir(void *exec)
{
	exec_redir_destroy(exec);
}

static void	_del_arg(void *exec)
{
	exec_arg_destroy(exec);
}

t_exec_simplecom	*exec_simplecom_destroy(t_exec_simplecom *exec)
{
	ft_lstclear(&(exec->redirs), _del_redir);
	ft_lstclear(&(exec->args), _del_arg);
	free(exec);
	return (NULL);
}
