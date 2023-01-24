/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "envmanager_internal.h"

int	_envman_export(t_list *envlist)
{
	int	stat;

	stat = 0;
	while (envlist)
	{
		if (((t_enventry *)(envlist->content))->val)
		{
			if (ft_printf("declare -x %s=\"%s\"\n",
					((t_enventry *)(envlist->content))->name,
				((t_enventry *)(envlist->content))->val) < 0)
				stat = 1;
		}
		else
		{
			if (ft_printf("declare -x %s\n",
					((t_enventry *)(envlist->content))->name) < 0)
				stat = 1;
		}
		envlist = envlist->next;
	}
	return (stat);
}

int	envman_export(void)
{
	return (_envmanager(ENVMANMODE_EXPORT, 0));
}
