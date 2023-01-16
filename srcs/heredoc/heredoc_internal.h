#ifndef HEREDOC_INTERNAL_H
# define HEREDOC_INTERNAL_H
# include "heredoc.h"
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

int	heredocmanager(int mode, int doc_id, void *buf);
int	heredoc_init_(int *n_heredoc, int *i_current, char **temp_dir);
int	heredoc_read_(int *n_heredoc, char *temp_dir, char *delimeter);
int	heredoc_get_filename_(
		int n_heredoc, char *temp_dir, int doc_id, char **buf);
int	heredoc_get_next_filename_(
		int n_heredoc, char *temp_dir, int *i_current, char **buf);
int	heredoc_clear_(int *n_heredoc, int *i_current, char *temp_dir, int doc_id);

#endif
