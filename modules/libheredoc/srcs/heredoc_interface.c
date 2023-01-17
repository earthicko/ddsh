#include "heredoc_internal.h"

int	heredoc_init(void)
{
	return (_heredocmanager(HEREDOCMODE_INIT, 0, 0));
}

int	heredoc_read(char *delimeter)
{
	return (_heredocmanager(HEREDOCMODE_READ, 0, delimeter));
}

int	heredoc_get_filename(int doc_id, char **buf)
{
	return (_heredocmanager(HEREDOCMODE_GETFILENAME, doc_id, buf));
}

int	heredoc_get_next_filename(char **buf)
{
	return (_heredocmanager(HEREDOCMODE_GETNEXTFILENAME, 0, buf));
}

int	heredoc_clear(int doc_id)
{
	return (_heredocmanager(HEREDOCMODE_CLEAR, doc_id, 0));
}
