#ifndef HEREDOC_H
# define HEREDOC_H

enum e_heredocmode
{
	HEREDOCMODE_READ = 0,
	HEREDOCMODE_GETFILENAME,
	HEREDOCMODE_CLEAR
};

int	heredocmanager(int mode, int doc_id, void *buf);

#endif
