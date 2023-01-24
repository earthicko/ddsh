/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:46 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "msgdef.h"
#include "executor_internal.h"

int	_io_manager(int mode)
{
	static int	backup[2];

	if (mode == STDINOUT_BACKUP)
	{
		backup[0] = dup(STDIN_FILENO);
		backup[1] = dup(STDOUT_FILENO);
		if (backup[0] < 0 || backup[1] < 0)
		{
			ft_dprintf(2, "%scritical I/O error: cannot redirect STDIN/OUT\n",
				MSG_ERROR_PREFIX);
			return (CODE_ERROR_IO);
		}
	}
	else if (mode == STDINOUT_RESTORE)
	{
		if (dup2(backup[0], STDIN_FILENO) < 0 || close(backup[0]) < 0
			|| dup2(backup[1], STDOUT_FILENO) < 0 || close(backup[1]) < 0)
		{
			ft_dprintf(2, "%scritical I/O error: cannot redirect STDIN/OUT\n",
				MSG_ERROR_PREFIX);
			return (CODE_ERROR_IO);
		}
	}
	return (CODE_OK);
}
