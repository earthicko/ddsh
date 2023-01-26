/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:09:47 by earth             #+#    #+#             */
/*   Updated: 2023/01/27 02:09:48 by earth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "t_node.h"
#include "t_execunit.h"

t_exec_redir	*exec_redir_create(t_node *root)
{
	t_exec_redir	*exec;
	char			*content;

	if (root->type != NODETYPE_IO_REDIRECT)
		return (NULL);
	exec = malloc(sizeof(t_exec_redir));
	if (!exec)
		return (NULL);
	ft_bzero(exec, sizeof(t_exec_redir));
	content = _get_nth_child(_get_nth_child(root, 0), 0)->content;
	if (ft_strncmp(content, "<<", 2) == 0)
		exec->type = REDIR_IN_HERE;
	else if (ft_strncmp(content, ">>", 2) == 0)
		exec->type = REDIR_OUT_APPEND;
	else if (ft_strncmp(content, "<", 1) == 0)
		exec->type = REDIR_IN;
	else if (ft_strncmp(content, ">", 1) == 0)
		exec->type = REDIR_OUT;
	exec->content = ft_strdup(
			_get_nth_child(_get_nth_child(root, 0), 1)->content);
	if (!exec->content)
		return (exec_redir_destroy(exec));
	return (exec);
}

t_exec_redir	*exec_redir_destroy(t_exec_redir *exec)
{
	if (exec->content)
		free(exec->content);
	free(exec);
	return (NULL);
}
