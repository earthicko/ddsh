/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:45:07 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:45:24 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	_init_is_builtin_command(char **parr)
{
	parr[0] = "";
	parr[1] = "cd";
	parr[2] = "echo";
	parr[3] = "export";
	parr[4] = "pwd";
	parr[5] = "unset";
	parr[6] = "env";
	parr[7] = "exit";
}

int	is_builtin_command(char *str)
{
	char	*dict[8];
	int		i;

	_init_is_builtin_command(dict);
	i = 1;
	while (i < 8)
	{
		if (ft_strncmp(str, dict[i], ft_strlen(dict[i]) + 1) == 0)
			return (i);
		i++;
	}
	return (FALSE);
}
