/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:53 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:51 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "libft.h"
#include "msgdef.h"
#include "strutils.h"
#include "heredoc_internal.h"

static int	_heredoc_clear_entry(char *ttyname, int n_heredoc, int doc_id)
{
	int		stat;
	char	*filename;

	stat = _heredoc_get_filename(ttyname, n_heredoc, doc_id, &filename);
	if (stat)
		return (stat);
	unlink(filename);
	free(filename);
	return (CODE_OK);
}

static int	_closedir_and_return(DIR *dp, int stat)
{
	closedir(dp);
	return (stat);
}

static int	_heredoc_clear_all(void)
{
	DIR				*dp;
	struct dirent	*ep;
	char			*full_path;

	dp = opendir(DIR_HEREDOC);
	if (!dp)
		return (CODE_ERROR_IO);
	while (TRUE)
	{
		ep = readdir(dp);
		if (!ep)
			break ;
		if (ep && ep->d_type == DT_REG
			&& !ft_strncmp(ep->d_name, PREFIX_HEREDOC_TEMPFILE,
				ft_strlen(PREFIX_HEREDOC_TEMPFILE)))
		{
			full_path = ft_strmerge(3, DIR_HEREDOC, "/", ep->d_name);
			if (!full_path)
				return (_closedir_and_return(dp, CODE_ERROR_MALLOC));
			unlink(full_path);
			free(full_path);
		}
	}
	return (_closedir_and_return(dp, CODE_OK));
}

int	_heredoc_clear(char *ttyname, int *n_heredoc, int *i_current, int doc_id)
{
	int	stat;

	if (doc_id < 0)
	{
		*n_heredoc = 0;
		*i_current = 0;
		stat = _heredoc_clear_all();
		if (stat == CODE_ERROR_IO)
			ft_dprintf(2, "%sfailed to open dir: %s\n",
				MSG_ERROR_PREFIX, DIR_HEREDOC);
		if (stat == CODE_ERROR_MALLOC)
			ft_print_error(MSG_ERROR_PREFIX, stat);
		return (stat);
	}
	else if (0 <= doc_id && doc_id < *n_heredoc)
	{
		if (_heredoc_clear_entry(ttyname, *n_heredoc, doc_id))
			return (CODE_ERROR_GENERIC);
		return (CODE_OK);
	}
	return (CODE_ERROR_SCOPE);
}
