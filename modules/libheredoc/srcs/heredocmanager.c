#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "heredoc_internal.h"

static int	heredoc_clear_entry(int n_heredoc, int doc_id)
{
	int		stat;
	char	*filename;

	stat = heredoc_get_filename(n_heredoc, doc_id, &filename);
	if (stat)
		return (stat);
	unlink(filename);
	free(filename);
	return (CODE_OK);
}

int	heredoc_clear(int *n_heredoc, int doc_id)
{
	int		i;

	if (doc_id < 0)
	{
		i = 0;
		while (i < *n_heredoc)
		{
			if (heredoc_clear_entry(*n_heredoc, i))
				return (CODE_ERROR_GENERIC);
			i++;
		}
	}
	else if (0 <= doc_id && doc_id < *n_heredoc)
	{
		if (heredoc_clear_entry(*n_heredoc, doc_id))
			return (CODE_ERROR_GENERIC);
		*n_heredoc = 0;
	}
	return (CODE_OK);
}

// mode: READ | GETFILENAME | CLEAR
// read: reads here_doc to doc_id, using delimeter (char *)buf
// getfilename: store filename of doc_id on (char **)buf
// clear: clear all docs if doc_id < 0, else clear doc_id
int	heredocmanager(int mode, int doc_id, void *buf)
{
	static int	n_heredoc;

	if (mode == HEREDOCMODE_READ)
		return (heredoc_read(&n_heredoc, doc_id, buf));
	if (mode == HEREDOCMODE_GETFILENAME)
		return (heredoc_get_filename(n_heredoc, doc_id, buf));
	if (mode == HEREDOCMODE_CLEAR)
		return (heredoc_clear(&n_heredoc, doc_id));
	return (CODE_ERROR_SCOPE);
}
