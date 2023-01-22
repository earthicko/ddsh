/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "envmanager_internal.h"

int	_envmanager(int mode, void *buf, char *name, char *val)
{
	static t_list	*envlist;

	if (mode == ENVMANMODE_INIT)
		return (_envman_init(&envlist, buf));
	else if (mode == ENVMANMODE_CLEAR)
		return (_envman_clear(&envlist));
	else if (mode == ENVMANMODE_GETVAL)
		return (_envman_getval(envlist, buf, name));
	else if (mode == ENVMANMODE_SETVAL)
		return (_envman_setval(&envlist, name, val));
	else if (mode == ENVMANMODE_UNSETVAL)
		return (_envman_unsetval(&envlist, name));
	else if (mode == ENVMANMODE_GETENVP)
		return (_envman_getenvp(envlist, buf));
	else if (mode == ENVMANMODE_EXPORT)
		return (_envman_export(envlist));
	return (CODE_ERROR_DATA);
}
