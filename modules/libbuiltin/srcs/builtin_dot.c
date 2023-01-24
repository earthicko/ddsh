/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:25 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "envmanager.h"
#include "prompt.h"
#include "msgdef.h"

static int	_builtin_dot_internal(char *arg)
{
	int		fd;
	char	*line;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "%s.: %s: ", MSG_ERROR_PREFIX, arg);
		perror(NULL);
		return (CODE_ERROR_IO);
	}
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			return (CODE_OK);
		execute_line(line);
		free(line);
	}
}

int	builtin_dot(char **argv)
{
	argv++;
	if (!*argv)
	{
		ft_dprintf(2, "%s.: filename argument required\n", MSG_ERROR_PREFIX);
		return (2);
	}
	while (*argv)
	{
		_builtin_dot_internal(*argv);
		argv++;
	}
	return (exit_stat_manager(-1));
}
