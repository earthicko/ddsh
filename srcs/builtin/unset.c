/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "envmanager.h"
#include "msgdef.h"
#include "strutils.h"

int	builtin_unset(char **argv)
{
	int	stat;

	stat = 0;
	argv++;
	while (*argv)
	{
		if (is_valid_name(*argv))
			envman_unsetval(*argv);
		else
		{
			if (ft_dprintf(2, "%sunset: `%s': not a valid identifier\n",
					MSG_ERROR_PREFIX, *argv) < 0)
				stat = 1;
		}
		argv++;
	}
	return (stat);
}
