/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:26 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:42:30 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_INTERNAL_H
# define HEREDOC_INTERNAL_H
# include "heredoc.h"
# define DIR_HEREDOC "/tmp"
# define PREFIX_HEREDOC_TEMPFILE ".heredoc_"
# define PREFIX_HEREDOC_PROMPT "> "

enum e_heredocmode
{
	HEREDOCMODE_INIT = 0,
	HEREDOCMODE_READ,
	HEREDOCMODE_GETFILENAME,
	HEREDOCMODE_GETNEXTFILENAME,
	HEREDOCMODE_CLEAR
};

int	_heredocmanager(int mode, int doc_id, void *buf);
int	_heredoc_read(
		char *ttyname, int *n_heredoc, char *delimeter);
int	_heredoc_get_filename(
		char *ttyname, int n_heredoc, int doc_id, char **buf);
int	_heredoc_get_next_filename(
		char *ttyname, int n_heredoc, int *i_current, char **buf);
int	_heredoc_clear(
		char *ttyname, int *n_heredoc, int *i_current);

#endif
