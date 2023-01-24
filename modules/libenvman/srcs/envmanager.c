/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "envmanager_internal.h"

int	_envmanager(int mode, t_envmaninfo *info)
{
	static t_list	*envlist;

	if (mode == ENVMANMODE_INIT)
		return (_envman_init(&envlist, info->buf));
	else if (mode == ENVMANMODE_CLEAR)
		return (_envman_clear(&envlist));
	else if (mode == ENVMANMODE_GETVAL)
		return (_envman_getval(envlist, info->buf, info->name));
	else if (mode == ENVMANMODE_SETVAL)
		return (_envman_setval(&envlist, info->name, info->val, info->exp));
	else if (mode == ENVMANMODE_UNSETVAL)
		return (_envman_unsetval(&envlist, info->name));
	else if (mode == ENVMANMODE_GETENVP)
		return (_envman_getenvp(envlist, info->buf));
	else if (mode == ENVMANMODE_EXPORT)
		return (_envman_export(envlist));
	return (CODE_ERROR_DATA);
}
