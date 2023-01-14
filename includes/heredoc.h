#ifndef HEREDOC_H
# define HEREDOC_H

enum e_heredocmode
{
	HEREDOCMODE_INIT = 0,
	HEREDOCMODE_READ,
	HEREDOCMODE_GETFILENAME,
	HEREDOCMODE_CLEAR
};

int	heredocmanager(int mode, int doc_id, void *buf);

#endif
