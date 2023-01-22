/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:32 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"
#include "msgdef.h"

int	builtin_exit(char **argv)
{
	int	stat;
	int	ret;

	if (!argv)
		exit(exit_stat_manager(-1));
	if (argv[1] && argv[2])
	{
		ft_dprintf(2, "%sexit: too many arguments\n", MSG_ERROR_PREFIX);
		return (1);
	}
	if (argv[1])
	{
		ret = ft_atoi_if_valid(argv[1], &stat);
		if (ret)
		{
			ft_dprintf(2, "%sexit: %s: numeric argument required\n",
				MSG_ERROR_PREFIX, argv[1]);
			stat = 2;
		}
		exit(stat);
	}
	exit(exit_stat_manager(-1));
}
