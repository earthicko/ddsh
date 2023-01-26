/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_pipeseq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:09:45 by earth             #+#    #+#             */
/*   Updated: 2023/01/27 02:09:46 by earth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "t_node.h"
#include "t_execunit.h"

static int	_exec_pipeseq_create_loop(
		t_node *root, t_exec_pipeseq *exec, int i)
{
	void	*content;

	content = exec_simplecom_create(_get_nth_child(root, i));
	if (content)
	{
		if (exec_lstadd(&(exec->simplecoms), content))
			return (CODE_ERROR_MALLOC);
		return (CODE_OK);
	}
	return (CODE_ERROR_DATA);
}

t_exec_pipeseq	*exec_pipeseq_create(t_node *root)
{
	t_exec_pipeseq	*exec;
	int				i;
	int				len;

	if (root->type != NODETYPE_PIPE_SEQUENCE)
		return (NULL);
	exec = malloc(sizeof(t_exec_pipeseq));
	if (!exec)
		return (NULL);
	ft_bzero(exec, sizeof(t_exec_pipeseq));
	len = ft_lstsize(root->childs);
	i = 0;
	while (i < len)
	{
		if (_exec_pipeseq_create_loop(root, exec, i))
			return (exec_pipeseq_destroy(exec));
		i++;
	}
	return (exec);
}

static void	_del_simplecom(void *exec)
{
	exec_simplecom_destroy(exec);
}

t_exec_pipeseq	*exec_pipeseq_destroy(t_exec_pipeseq *exec)
{
	ft_lstclear(&(exec->simplecoms), _del_simplecom);
	free(exec);
	return (NULL);
}

t_exec_simplecom	*get_nth_simplecom(t_exec_pipeseq *exec, int n)
{
	return (get_nth_exec(exec->simplecoms, n));
}
