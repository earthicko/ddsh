/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_setval.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:45 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager_internal.h"

int	_envman_setval(t_list **envlist, char *name, char *val)
{
	t_enventry	*entry;
	char		*temp;

	if (val == ENVMAN_NULLVAL)
		val = NULL;
	entry = _envman_getentry(*envlist, name);
	if (entry && val)
	{
		temp = ft_strdup(val);
		if (!temp)
			return (CODE_ERROR_MALLOC);
		free(entry->val);
		entry->val = temp;
	}
	else if (!entry)
	{
		if (!is_valid_name(name))
			return (CODE_ERROR_DATA);
		return (_envman_addentry_nameval(envlist, name, val));
	}
	return (CODE_OK);
}

int	envman_setval(char *name, char *val)
{
	int	stat;

	stat = _envmanager(ENVMANMODE_SETVAL, 0, name, val);
	if (stat && stat != CODE_ERROR_DATA)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
