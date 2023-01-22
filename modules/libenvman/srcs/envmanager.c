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

// init: set envp
// clear: set none
// getval: set (char **)buf, name
// setval: set name, val
// unsetval: set name
// getenvp: set (char ***)buf
int	_envmanager(char **envp, void *buf, char *name, char *val)
{
	static t_list	*envlist;

	if (envp && !buf && !name && !val)
		return (_envman_init(&envlist, envp));
	else if (!envp && !buf && !name && !val)
		return (_envman_clear(&envlist));
	else if (!envp && buf && name && !val)
		return (_envman_getval(envlist, buf, name));
	else if (!envp && !buf && name && val)
		return (_envman_setval(&envlist, name, val));
	else if (!envp && !buf && name && !val)
		return (_envman_unsetval(&envlist, name));
	else if (!envp && buf && !name && !val)
		return (_envman_getenvp(envlist, buf));
	return (CODE_ERROR_DATA);
}
