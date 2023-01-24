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

int	_envman_setval(t_list **envlist, char *name, char *val, int exp)
{
	t_enventry	*entry;
	char		*temp;

	entry = _envman_getentry(*envlist, name);
	if (entry && val)
	{
		temp = ft_strdup(val);
		if (!temp)
			return (CODE_ERROR_MALLOC);
		free(entry->val);
		entry->val = temp;
		entry->exp = exp;
	}
	else if (!entry)
	{
		if (!is_valid_name(name))
			return (CODE_ERROR_DATA);
		return (_envman_addentry_nameval(envlist, name, val, exp));
	}
	return (CODE_OK);
}

int	envman_setval(char *name, char *val, int exp)
{
	int				stat;
	t_envmaninfo	info;

	info.name = name;
	info.val = val;
	info.exp = exp;
	stat = _envmanager(ENVMANMODE_SETVAL, &info);
	if (stat && stat != CODE_ERROR_DATA)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
