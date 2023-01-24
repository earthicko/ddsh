/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocmanager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:52 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "msgdef.h"
#include "heredoc_internal.h"

static char	*_extract_ttyslotname(void)
{
	char	*slotname;
	char	*slot_i;

	slot_i = ft_itoa(ttyslot());
	if (!slot_i)
		return (NULL);
	slotname = ft_strjoin("ttys", slot_i);
	free(slot_i);
	return (slotname);
}

static int	_heredoc_init(int *n_heredoc, int *i_current, char **_ttyname)
{
	if (*_ttyname)
		return (CODE_OK);
	*_ttyname = _extract_ttyslotname();
	if (!(*_ttyname))
	{
		ft_dprintf(2, "%sfailed to fetch ttyname\n", MSG_ERROR_PREFIX);
		return (CODE_ERROR_IO);
	}
	return (_heredoc_clear(*_ttyname, n_heredoc, i_current));
}

// mode: INIT | READ | GETFILENAME | CLEAR
// init: gets tty slot name to be saved
// read: reads here_doc to doc_id, using delimeter (char *)buf
// getfilename: store filename of doc_id on (char **)buf
// getnextfilename: store filename of next doc_id on (char **)buf
// clear: clear all docs if doc_id < 0, else clear doc_id
int	_heredocmanager(int mode, int doc_id, void *buf)
{
	static int	n_heredoc;
	static int	i_current;
	static char	*_ttyname;

	if (mode == HEREDOCMODE_INIT)
		return (_heredoc_init(&n_heredoc, &i_current, &_ttyname));
	if (!_ttyname)
	{
		ft_dprintf(2, "%sfailed to fetch ttyname\n", MSG_ERROR_PREFIX);
		return (CODE_ERROR_IO);
	}
	if (mode == HEREDOCMODE_READ)
		return (_heredoc_read(
				_ttyname, &n_heredoc, buf));
	if (mode == HEREDOCMODE_GETFILENAME)
		return (_heredoc_get_filename(
				_ttyname, n_heredoc, doc_id, buf));
	if (mode == HEREDOCMODE_GETNEXTFILENAME)
		return (_heredoc_get_next_filename(
				_ttyname, n_heredoc, &i_current, buf));
	if (mode == HEREDOCMODE_CLEAR)
		return (_heredoc_clear(
				_ttyname, &n_heredoc, &i_current));
	return (CODE_ERROR_SCOPE);
}
