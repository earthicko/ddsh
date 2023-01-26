/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:09:43 by earth             #+#    #+#             */
/*   Updated: 2023/01/27 02:09:44 by earth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "t_node.h"
#include "t_execunit.h"

t_exec_arg	*exec_arg_create(t_node *root)
{
	t_exec_arg	*exec;

	if (root->type != NODETYPE_CMD_WORD)
		return (NULL);
	exec = malloc(sizeof(t_exec_arg));
	if (!exec)
		return (NULL);
	ft_bzero(exec, sizeof(t_exec_arg));
	exec->content = ft_strdup(root->content);
	if (!exec)
		return (exec_arg_destroy(exec));
	return (exec);
}

t_exec_arg	*exec_arg_destroy(t_exec_arg *exec)
{
	if (exec->content)
		free(exec->content);
	free(exec);
	return (NULL);
}
