/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_addentry.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:45 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "envmanager_internal.h"

int	_envman_addentry_str(t_list **p_list, char *str)
{
	t_list		*newlst;
	t_enventry	*entry;
	int			stat;

	entry = malloc(sizeof(t_enventry));
	if (!entry)
		return (CODE_ERROR_MALLOC);
	ft_memset(entry, 0, sizeof(t_enventry));
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

static int	_envman_addentry_nameval_set(t_enventry *ent, char **dst, char *src)
{
	*dst = ft_strdup(src);
	if (!(*dst))
	{
		_enventry_destroy(ent);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

int	_envman_addentry_nameval(t_list **p_list, char *name, char *val)
{
	t_list		*newlst;
	t_enventry	*entry;

	entry = malloc(sizeof(t_enventry));
	if (!entry)
		return (CODE_ERROR_MALLOC);
	ft_memset(entry, 0, sizeof(t_enventry));
	if (name && _envman_addentry_nameval_set(entry, &(entry->name), name))
		return (CODE_ERROR_MALLOC);
	if (val && _envman_addentry_nameval_set(entry, &(entry->val), val))
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
