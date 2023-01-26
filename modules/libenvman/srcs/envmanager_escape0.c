/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager_specialval_escape0.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "prompt_string.h"

char	*_envman_escape_reset(void)
{
	return (ft_strdup(ANSI_RESET));
}

char	*_envman_escape_red(void)
{
	return (ft_strdup(ANSI_RED));
}

char	*_envman_escape_green(void)
{
	return (ft_strdup(ANSI_GREEN));
}

char	*_envman_escape_yellow(void)
{
	return (ft_strdup(ANSI_YELLOW));
}

char	*_envman_escape_blue(void)
{
	return (ft_strdup(ANSI_BLUE));
}
