/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:53 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:51 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_internal.h"
#include "libft.h"
#include "msgdef.h"

int	heredoc_init(void)
{
	return (_heredocmanager(HEREDOCMODE_INIT, 0, 0));
}

int	heredoc_read(char *delimeter)
{
	int	stat;

	stat = _heredocmanager(HEREDOCMODE_READ, 0, delimeter);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}

int	heredoc_get_filename(int doc_id, char **buf)
{
	int	stat;

	stat = _heredocmanager(HEREDOCMODE_GETFILENAME, doc_id, buf);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}

int	heredoc_get_next_filename(char **buf)
{
	int	stat;

	stat = _heredocmanager(HEREDOCMODE_GETNEXTFILENAME, 0, buf);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}

int	heredoc_clear(void)
{
	int	stat;

	stat = _heredocmanager(HEREDOCMODE_CLEAR, 0, 0);
	if (stat)
		ft_print_error(MSG_ERROR_PREFIX, stat);
	return (stat);
}
