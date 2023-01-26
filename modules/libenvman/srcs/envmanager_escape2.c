/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_specialval_escape2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "prompt_string.h"

char	*_envman_escape_bgreen(void)
{
	return (ft_strdup(ANSI_BGREEN));
}

char	*_envman_escape_byellow(void)
{
	return (ft_strdup(ANSI_BYELLOW));
}

char	*_envman_escape_bblue(void)
{
	return (ft_strdup(ANSI_BBLUE));
}

char	*_envman_escape_bmagenta(void)
{
	return (ft_strdup(ANSI_BMAGENTA));
}

char	*_envman_escape_bcyan(void)
{
	return (ft_strdup(ANSI_BCYAN));
}
