/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_unsetval.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:45 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envmanager_internal.h"
#include "msgdef.h"
#include "libft.h"

int	_envman_unsetval(t_list **envlist, char *name)
{
	t_list	*list;

	list = _find_list_with_entry(*envlist, name);
	if (!list)
		return (CODE_ERROR_DATA);
	ft_lstunlink(envlist, list, _free_entry);
	return (CODE_OK);
}

int	envman_unsetval(char *name)
{
	int				stat;
	t_envmaninfo	info;

	info.name = name;
	stat = _envmanager(ENVMANMODE_UNSETVAL, &info);
	if (stat && stat != CODE_ERROR_DATA)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
