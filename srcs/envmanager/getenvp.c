/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_getenvp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager_internal.h"

int	_envman_getenvp(t_list *envlist, char ***buf)
{
	char	**cursor;

	*buf = malloc(sizeof(char *) * (ft_lstsize(envlist) + 1));
	if (!(*buf))
		return (CODE_ERROR_MALLOC);
	ft_bzero(*buf, sizeof(char *) * (ft_lstsize(envlist) + 1));
	cursor = *buf;
	while (envlist)
	{
		if (((t_enventry *)(envlist->content))->val
			&& ((t_enventry *)(envlist->content))->exp)
		{
			*cursor = envman_compose_envstr(envlist->content);
			if (!(*cursor))
			{
				ft_free_strarr(*buf);
				*buf = NULL;
				return (CODE_ERROR_MALLOC);
			}
			cursor++;
		}
		envlist = envlist->next;
	}
	return (CODE_OK);
}

int	envman_getenvp(char ***buf)
{
	int				stat;
	t_envmaninfo	info;

	info.buf = buf;
	stat = _envmanager(ENVMANMODE_GETENVP, &info);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
