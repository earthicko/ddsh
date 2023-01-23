/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_from_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:45:21 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:45:24 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "libft.h"
#include "msgdef.h"
#include "envmanager.h"
#include "strutils.h"

static int	_closedir_and_return(DIR *d, int stat)
{
	closedir(d);
	return (stat);
}

static int	_replace_if_found(char *dir_path, char **buf)
{
	DIR				*d;
	struct dirent	*dir;
	char			*backup;

	d = opendir(dir_path);
	if (!d)
		return (CODE_ERROR_IO);
	while (TRUE)
	{
		dir = readdir(d);
		if (!dir)
			return (_closedir_and_return(d, 1));
		if (dir->d_type == DT_REG
			&& ft_strncmp(dir->d_name, *buf, ft_strlen(*buf) + 1) == 0)
		{
			backup = ft_strmerge(3, dir_path, "/", dir->d_name);
			if (!backup)
				return (_closedir_and_return(d, CODE_ERROR_MALLOC));
			free(*buf);
			*buf = backup;
			return (_closedir_and_return(d, CODE_OK));
		}
	}
}

static int	_find_exec_from_path_abort(char *path, char **paths, int stat)
{
	free(path);
	if (paths)
		ft_free_strarr(paths);
	return (stat);
}

int	_find_exec_from_path(char **buf)
{
	char	*path;
	char	**paths;
	char	**cursor;
	int		stat;

	if (envman_getval("PATH", &path))
	{
		ft_dprintf(2, "%s%s: No such file or directory\n",
			MSG_ERROR_PREFIX, *buf);
		return (CODE_ERROR_GENERIC);
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (_find_exec_from_path_abort(path, paths, CODE_ERROR_MALLOC));
	cursor = paths;
	while (*cursor)
	{
		stat = _replace_if_found(*cursor, buf);
		if (stat == CODE_OK || stat == CODE_ERROR_MALLOC)
			return (_find_exec_from_path_abort(path, paths, stat));
		cursor++;
	}
	ft_dprintf(2, "%s%s: command not found\n", MSG_ERROR_PREFIX, *buf);
	return (_find_exec_from_path_abort(path, paths, CODE_ERROR_GENERIC));
}
