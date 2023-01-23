/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_enventry.c                                       :+:      :+:    :+:   */
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

t_enventry	*_enventry_destroy(t_enventry *enventry)
{
	if (!enventry)
		return (NULL);
	if (enventry->name)
		free(enventry->name);
	if (enventry->val)
		free(enventry->val);
	free(enventry);
	return (NULL);
}

void	_free_entry(void *content)
{
	_enventry_destroy(content);
}

t_list	*_find_list_with_entry(t_list *envlist, char *name)
{
	char	*lstname;

	while (envlist)
	{
		lstname = ((t_enventry *)(envlist->content))->name;
		if (!ft_strncmp(name, lstname, ft_strlen(lstname) + 1))
			return (envlist);
		envlist = envlist->next;
	}
	return (NULL);
}

t_enventry	*_envman_getentry(t_list *envlist, char *name)
{
	t_list	*list;

	list = _find_list_with_entry(envlist, name);
	if (list)
		return (list->content);
	return (NULL);
}
