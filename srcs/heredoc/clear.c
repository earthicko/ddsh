/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:53 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:51 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "libft.h"
#include "msgdef.h"
#include "strutils.h"
#include "heredoc_internal.h"

static int	_closedir_and_return(DIR *dp, int stat)
{
	closedir(dp);
	return (stat);
}

static int	_should_delete(char *_ttyname, struct dirent *ep)
{
	char	*prefix;
	int		stat;

	prefix = ft_strjoin(PREFIX_HEREDOC_TEMPFILE, _ttyname);
	if (!prefix)
		return (CODE_ERROR_MALLOC);
	stat = (ep && ep->d_type == DT_REG
			&& !ft_strncmp(ep->d_name, prefix, ft_strlen(prefix)));
	free(prefix);
	if (stat)
		return (TRUE);
	return (FALSE);
}

static int	_heredoc_clear_entry(struct dirent *ep)
{
	char	*full_path;

	full_path = ft_strmerge(3, DIR_HEREDOC, "/", ep->d_name);
	if (!full_path)
		return (CODE_ERROR_MALLOC);
	unlink(full_path);
	free(full_path);
	return (CODE_OK);
}

static int	_heredoc_clear_all(char *_ttyname)
{
	DIR				*dp;
	struct dirent	*ep;
	int				stat;

	dp = opendir(DIR_HEREDOC);
	if (!dp)
		return (CODE_ERROR_IO);
	while (TRUE)
	{
		ep = readdir(dp);
		if (!ep)
			break ;
		stat = _should_delete(_ttyname, ep);
		if (stat < 0)
			return (_closedir_and_return(dp, CODE_ERROR_MALLOC));
		if (stat == TRUE && _heredoc_clear_entry(ep))
			return (_closedir_and_return(dp, CODE_ERROR_MALLOC));
	}
	return (_closedir_and_return(dp, CODE_OK));
}

int	_heredoc_clear(char *ttyname, int *n_heredoc, int *i_current)
{
	int	stat;

	*n_heredoc = 0;
	*i_current = 0;
	stat = _heredoc_clear_all(ttyname);
	if (stat == CODE_ERROR_IO)
		ft_dprintf(2, "%sfailed to open dir: %s\n",
			MSG_ERROR_PREFIX, DIR_HEREDOC);
	if (stat == CODE_ERROR_MALLOC)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
