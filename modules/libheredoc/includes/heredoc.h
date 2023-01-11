#ifndef HEREDOC_H
# define HEREDOC_H

enum e_heredocmode
{
	HEREDOCMODE_CREATE = 0,
	HEREDOCMODE_GETFD,
	HEREDOCMODE_CLEAR
};

int	heredocmanager(int mode, int doc_id, char *delimeter);

#endif
