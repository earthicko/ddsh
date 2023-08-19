/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:26 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:42:30 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_INTERNAL_H
# define HEREDOC_INTERNAL_H
# include "heredoc.h"
# define PREFIX_HEREDOC_TEMPFILE ".heredoc"
# define PREFIX_HEREDOC_PROMPT "> "
# ifndef DIR_HEREDOC
#  define DIR_HEREDOC "/tmp"
# endif

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
		char *shellname, int *n_heredoc, char *delimeter);
int	_heredoc_get_filename(
		char *shellname, int n_heredoc, int doc_id, char **buf);
int	_heredoc_get_next_filename(
		char *shellname, int n_heredoc, int *i_current, char **buf);
int	_heredoc_clear(
		char *shellname, int *n_heredoc, int *i_current);

#endif
