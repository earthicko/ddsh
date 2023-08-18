/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_specialval_escape1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ansi_escape.h"

char	*_envman_escape_magenta(void)
{
	return (ft_strdup(ANSI_MAGENTA));
}

char	*_envman_escape_cyan(void)
{
	return (ft_strdup(ANSI_CYAN));
}

char	*_envman_escape_white(void)
{
	return (ft_strdup(ANSI_WHITE));
}

char	*_envman_escape_bblack(void)
{
	return (ft_strdup(ANSI_BBLACK));
}

char	*_envman_escape_bred(void)
{
	return (ft_strdup(ANSI_BRED));
}
