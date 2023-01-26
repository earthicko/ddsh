/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_simplecom_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:09:49 by earth             #+#    #+#             */
/*   Updated: 2023/01/27 02:09:50 by earth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "t_execunit.h"

int	exec_simplecom_getargv(t_exec_simplecom *exec, char ***buf)
{
	int		i;
	int		len;
	char	**temp;

	len = ft_lstsize(exec->args);
	temp = malloc(sizeof(char *) * (len + 1));
	if (!temp)
		return (CODE_ERROR_MALLOC);
	ft_bzero(temp, sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		temp[i] = ft_strdup(get_nth_arg(exec, i)->content);
		if (!temp[i])
		{
			ft_free_strarr(temp);
			return (CODE_ERROR_MALLOC);
		}
		i++;
	}
	*buf = temp;
	return (CODE_OK);
}

t_exec_redir	*get_nth_redir(t_exec_simplecom *exec, int n)
{
	return (get_nth_exec(exec->redirs, n));
}

t_exec_arg	*get_nth_arg(t_exec_simplecom *exec, int n)
{
	return (get_nth_exec(exec->args, n));
}
