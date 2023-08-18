/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_getentry.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:45 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "envmanager_internal.h"

int	_envman_getentry(t_list *envlist, t_enventry *buf, char *name)
{
	t_enventry	*target;

	target = _enventry_getentry(envlist, name);
	if (!target)
		return (CODE_ERROR_DATA);
	ft_memcpy(buf, target, sizeof(t_enventry));
	return (CODE_OK);
}

int	envman_getentry(t_enventry *buf, char *name)
{
	t_envmaninfo	info;

	info.buf = buf;
	info.name = name;
	return (_envmanager(ENVMANMODE_GETENTRY, &info));
}
