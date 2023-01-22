/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:45:20 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:45:24 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"
#include "msgdef.h"
#include "strutils.h"

int	_find_exec_from_path(char **buf);

int	_is_file_existent(char *path)
{
	struct stat	buf;

	if (stat(path, &buf))
		return (FALSE);
	return (TRUE);
}

// replace word with absolute path and return 0.
// if not found in path return CODE_ERROR_GENERIC.
// only checks if file exists.
int	find_exec(char **buf)
{
	if (!(*buf))
		return (CODE_ERROR_DATA);
	if (ft_strchr(*buf, '/'))
	{
		if (_is_file_existent(*buf))
			return (CODE_OK);
		ft_dprintf(2, "%s%s: No such file or directory\n",
			MSG_ERROR_PREFIX, *buf);
		return (CODE_ERROR_GENERIC);
	}
	return (_find_exec_from_path(buf));
}
