#ifndef HEREDOC_INTERNAL_H
# define HEREDOC_INTERNAL_H
# include "heredoc.h"
# define DIR_HEREDOC "/tmp"
# define PREFIX_HEREDOC_TEMPFILE ".heredoc_"
# define PREFIX_HEREDOC_PROMPT "> "

enum e_heredocmode
{
	HEREDOCMODE_READ = 0,
	HEREDOCMODE_GETFILENAME,
	HEREDOCMODE_GETNEXTFILENAME,
	HEREDOCMODE_CLEAR
};

int	_heredocmanager(int mode, int doc_id, void *buf);
int	_heredoc_read(int *n_heredoc, char *delimeter);
int	_heredoc_get_filename(int n_heredoc, int doc_id, char **buf);
int	_heredoc_get_next_filename(int n_heredoc, int *i_current, char **buf);
int	_heredoc_clear(int *n_heredoc, int *i_current, int doc_id);

#endif
