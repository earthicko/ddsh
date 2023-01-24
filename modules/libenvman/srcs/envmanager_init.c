/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msgdef.h"
#include "envmanager_internal.h"

int	_envman_init(t_list **p_list, char **envp)
{
	int	stat;

	if (*p_list)
		_envman_clear(p_list);
	while (*envp)
	{
		stat = _envman_addentry_str(p_list, *envp, TRUE);
		if (stat)
		{
			_envman_clear(p_list);
			return (stat);
		}
		envp++;
	}
	return (CODE_OK);
}

int	envman_init(char **envp)
{
	int				stat;
	t_envmaninfo	info;

	info.buf = envp;
	stat = _envmanager(ENVMANMODE_INIT, &info);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
