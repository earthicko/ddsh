/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "envmanager_internal.h"

int	_envman_clear(t_list **p_list)
{
	if (*p_list)
		ft_lstclear(p_list, _free_entry);
	return (CODE_OK);
}

int	envman_clear(void)
{
	return (_envmanager(ENVMANMODE_CLEAR, 0, 0, 0));
}
