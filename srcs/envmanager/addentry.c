/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_addentry.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:45 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "envmanager_internal.h"

int	_envman_addentry_str(t_list **p_list, char *str, int exp)
{
	t_list		*newlst;
	t_enventry	*entry;
	int			stat;

	entry = _enventry_create(NULL, NULL, exp);
	if (!entry)
		return (CODE_ERROR_MALLOC);
	stat = envman_split_envstr(str, &(entry->name), &(entry->val));
	if (stat)
	{
		_enventry_destroy(entry);
		return (stat);
	}
	newlst = ft_lstnew(entry);
	if (!newlst)
	{
		_enventry_destroy(entry);
		return (CODE_ERROR_MALLOC);
	}
	ft_lstadd_back(p_list, newlst);
	return (CODE_OK);
}

int	_envman_addentry_nameval(t_list **p_list, char *name, char *val, int exp)
{
	t_list		*newlst;
	t_enventry	*entry;

	entry = _enventry_create(name, val, exp);
	if (!entry)
		return (CODE_ERROR_MALLOC);
	newlst = ft_lstnew(entry);
	if (!newlst)
	{
		_enventry_destroy(entry);
		return (CODE_ERROR_MALLOC);
	}
	ft_lstadd_back(p_list, newlst);
	return (CODE_OK);
}
